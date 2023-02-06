// Copyright di-tri.


#include "ROH_BlobActor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

AROH_BlobActor::AROH_BlobActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Blob Collision"));
	SphereComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	SphereComponent->CanCharacterStepUpOn = ECB_No;
	SphereComponent->SetShouldUpdatePhysicsVolume(true);
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->bDynamicObstacle = true;
	SphereComponent->SetSphereRadius(BlobRaduis);
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Blob Mesh"));
	if (StaticMeshComponent)
	{
		StaticMeshComponent->bOwnerNoSee = false;
		StaticMeshComponent->bCastDynamicShadow = false;
		StaticMeshComponent->bAffectDynamicIndirectLighting = true;
		StaticMeshComponent->bUseDefaultCollision = false;
		StaticMeshComponent->SetWorldScale3D(FVector(BlobRaduis / 160.0f));
		StaticMeshComponent->SetupAttachment(SphereComponent);
	}

	BoxDynamicCollider = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Blob Box Dynamic Collider"));
	if (BoxDynamicCollider)
	{
		BoxDynamicCollider->SetBoxExtent(FVector(BlobRaduis));
		BoxDynamicCollider->OnComponentBeginOverlap.AddDynamic(this, &AROH_BlobActor::OnOverlapBegin);       // set up a notification for when this component overlaps something
		BoxDynamicCollider->OnComponentEndOverlap.AddDynamic(this, &AROH_BlobActor::OnOverlapEnd);       // set up a notification for when this component overlaps something
		BoxDynamicCollider->SetupAttachment(SphereComponent);
	}

}

void AROH_BlobActor::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

	const FVector scale = FMath::Lerp(GetActorScale(), TargetBlobScale, DeltaTime * LightReactionSpeed);
	SetActorScale3D(scale);

	ResetInteractionWithLight();
}


void AROH_BlobActor::ResetInteractionWithLight()
{
	IROH_LightReactableInterface::ResetInteractionWithLight();

	TargetBlobScale = FVector(1.0f);
}

void AROH_BlobActor::ReactToLight(float lightDistance)
{
	IROH_LightReactableInterface::ReactToLight(lightDistance);


	const float lightRecievedValue = FMath::Clamp(
		UKismetMathLibrary::InverseLerp(MinMaxLightReactThresholds.X, MinMaxLightReactThresholds.Y, TotalInteraction),
		0.0f, 1.0f);

	TargetBlobScale = FVector(1.0f - lightRecievedValue);

	// TODO: Replace with tolerance value
	if (lightRecievedValue > BoxDynamicLightThreshold)
	{
		BoxDynamicCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		BoxDynamicCollider->SetCollisionEnabled(BoxColliderType);
	}
}

void AROH_BlobActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, OtherActor->GetName() + "Started");
	}
}

void AROH_BlobActor::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, OtherActor->GetName() + "Ended");
	}
}

#if WITH_EDITOR
void AROH_BlobActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobActor, BlobRaduis))
	{
		SphereComponent->SetSphereRadius(BlobRaduis);
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetWorldScale3D(FVector(BlobRaduis / 160.0f));
			BoxDynamicCollider->SetBoxExtent(FVector(BlobRaduis));
		}
	}
	Super::PostEditChangeProperty(e);
}
#endif

void AROH_BlobActor::BeginPlay()
{
	AActor::BeginPlay();
	
	if (BoxDynamicCollider)
	{
		BoxColliderType = BoxDynamicCollider->GetCollisionEnabled();
	}
}