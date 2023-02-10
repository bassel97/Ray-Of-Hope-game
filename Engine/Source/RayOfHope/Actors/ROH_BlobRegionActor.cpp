// Copyright di-tri.


#include "ROH_BlobRegionActor.h"
#include "ROH_BlobActor.h"
#include "Components/BoxComponent.h"


AROH_BlobRegionActor::AROH_BlobRegionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Blob Box Dynamic Collider"));
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BoxCollider;

}

void AROH_BlobRegionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AROH_BlobRegionActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, BlobBoxSize)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, XAxisnumber)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, YAxisnumber)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, ZAxisnumber)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, RandomScale)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, CollapseToCenterAmount))
	{
		EditBlobBox();
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, BlobMinMaxLightReactThresholds)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, BlobLightReactionSpeed))

	{
		EditIndividualBlobs();
	}

	Super::PostEditChangeProperty(e);
}

void AROH_BlobRegionActor::EditBlobBox()
{
	BoxCollider->SetBoxExtent(BlobBoxSize);

	for (AROH_BlobActor* blob : BlobsArray)
	{
		if (blob)
		{
			blob->Destroy();
		}
	}
	BlobsArray.Empty();

	if (GetWorld() != nullptr && BlobActor.GetDefaultObject() != nullptr)
	{
		const FVector spawnOrigin = BoxCollider->Bounds.GetBox().GetCenter();
		const FVector AxisVector = FVector(XAxisnumber, YAxisnumber, ZAxisnumber);

		for (int8 x = -XAxisnumber + 1; x < XAxisnumber; x += 2)
		{
			for (int8 y = -YAxisnumber + 1; y < YAxisnumber; y += 2)
			{
				for (int8 z = -ZAxisnumber + 1; z < ZAxisnumber; z +=2)
				{
					const FVector indexVector = FVector(x, y, z);
					const FVector relativeLocation = spawnOrigin + (indexVector / AxisVector) * BlobBoxSize;

					const FVector offset = (spawnOrigin - relativeLocation) * CollapseToCenterAmount;

					AROH_BlobActor* blob = GetWorld()->SpawnActor<AROH_BlobActor>(BlobActor,
						GetActorLocation(), GetActorRotation());
					BlobsArray.Add(blob);
					
					blob->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					blob->SetActorLocation(relativeLocation + offset);
					blob->SetBlobRaduis(BlobBoxSize.GetMin() * FMath::RandRange(RandomScale.X, RandomScale.Y));
				}
			}
		}
	}

	EditIndividualBlobs();
}

void AROH_BlobRegionActor::EditIndividualBlobs()
{
	for (AROH_BlobActor* blob : BlobsArray)
	{
		if (blob != nullptr)
		{
			blob->SetMinMaxLightReactThresholds(BlobMinMaxLightReactThresholds);
			blob->SetLightReactionSpeed(BlobLightReactionSpeed);
		}
	}
}

#endif

void AROH_BlobRegionActor::BeginPlay()
{
	Super::BeginPlay();
	
}