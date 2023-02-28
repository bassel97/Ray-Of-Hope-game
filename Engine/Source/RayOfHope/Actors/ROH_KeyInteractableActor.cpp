// Copyright di-tri.


#include "ROH_KeyInteractableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RayOfHope/Actors/ROH_KeyTargetParent.h"
#include "RayOfHope/Actors/ROH_KeyTargetConnector.h"

AROH_KeyInteractableActor::AROH_KeyInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	KeyStaticMesh->CanCharacterStepUpOn = ECB_No;
	KeyStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyStaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	RootComponent = KeyStaticMesh;

	KeyBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Key Box Collider"));
	KeyBoxCollider->CanCharacterStepUpOn = ECB_No;
	KeyBoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	KeyBoxCollider->SetCollisionObjectType(ECC_WorldStatic);
	KeyBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AROH_KeyInteractableActor::OnKeyOverlapBegin);       // set up a notification for when this component overlaps something
	KeyBoxCollider->OnComponentEndOverlap.AddDynamic(this, &AROH_KeyInteractableActor::OnKeyOverlapEnd);       // set up a notification for when this component overlaps something
	KeyBoxCollider->SetupAttachment(KeyStaticMesh);

	KeyTargetLineOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("Key Target Line Origin"));
	if (KeyTargetLineOrigin)
	{
		KeyTargetLineOrigin->SetupAttachment(RootComponent);
	}
}

void AROH_KeyInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const bool shouldOpenTarget = bShouldOpenByLight || bShouldOpenByCollision;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, shouldOpenTarget?"shouldOpenTarget":"should not OpenTarget");
	if (bShouldOpenByLightPrevious != shouldOpenTarget)
	{
		InteractWithTargets(shouldOpenTarget);
	}
	bShouldOpenByLightPrevious = shouldOpenTarget;
}

void AROH_KeyInteractableActor::ResetInteractionWithLight()
{
	IROH_LightReactableInterface::ResetInteractionWithLight();

}

void AROH_KeyInteractableActor::ReactToLight(float lightDistance)
{
	IROH_LightReactableInterface::ReactToLight(lightDistance);

	if (bCanInteractWithLight)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(lightDistance));
	}

	bShouldOpenByLight = bCanInteractWithLight && lightDistance > LightInteractionThreshold;
}


void AROH_KeyInteractableActor::OnKeyOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(!bCanInteractWithDynamicObjects)
	{
		return;
	}

	NumberOfObjectsInCollider++;
	if (NumberOfObjectsInCollider > 0)
	{
		bShouldOpenByCollision = true;
	}
}

void AROH_KeyInteractableActor::OnKeyOverlapEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!bCanInteractWithDynamicObjects)
	{
		return;
	}

	NumberOfObjectsInCollider--;
	if (NumberOfObjectsInCollider <= 0)
	{
		bShouldOpenByCollision = false;
	}
}

void AROH_KeyInteractableActor::SetUpKeyTargets()
{
	for (FROH_KeyTargetStruct& keyTarget : KeyTargets)
	{
		if (AROH_KeyTargetParent* target = keyTarget.Target.Get())
		{
			if (keyTarget.Connector.IsNull())
			{
				//keyTarget.Connector.Get()->Destroy();
				keyTarget.Connector = GetWorld()->SpawnActor<AROH_KeyTargetConnector>(
					KeyTargetConnector,
					GetActorLocation(), GetActorRotation());
			}
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, KeyTargetLineOrigin->GetComponentLocation().ToString());
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, keyTarget.Target->GetKeyTargetLineOriginLocation().ToString());

			keyTarget.Connector->SetStartEndPoints(
				KeyTargetLineOrigin->GetComponentLocation(),
				keyTarget.Target->GetKeyTargetLineOriginLocation()
			);

			keyTarget.Connector->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			//keyTarget.Connector = connector;
		}
	}
}

#if WITH_EDITOR
void AROH_KeyInteractableActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_KeyInteractableActor, KeyTargets))
	{
		SetUpKeyTargets();
	}
	Super::PostEditChangeProperty(e);
}
#endif

void AROH_KeyInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AROH_KeyInteractableActor::InteractWithTargets(bool isOpening)
{
	if (!isOpening && bIsOneTimePress)
	{
		return;
	}

	if (bCanInteractWithDynamicObjects || bCanInteractWithLight)
	{
		for (FROH_KeyTargetStruct keyTarget : KeyTargets)
		{
			if (AROH_KeyTargetParent* target = keyTarget.Target.Get())
			{
				if (isOpening)
				{
					target->OpenTarget();
					if (keyTarget.Connector.Get())
					{
						keyTarget.Connector.Get()->OnOpenTarget();
					}
				}
				else
				{
					target->CloseTarget();
					if (keyTarget.Connector.Get())
					{
						keyTarget.Connector.Get()->OnCloseTarget();
					}
				}
			}
		}
	}
}
