// Copyright di-tri.


#include "ROH_LightEmitterComponent.h"
#include "RayOfHope/Interfaces/ROH_LightReactableInterface.h"
#include "Kismet/KismetSystemLibrary.h"


UROH_LightEmitterComponent::UROH_LightEmitterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UROH_LightEmitterComponent::SetRaduis(float raduis)
{
	LightRaduis = raduis;
}

void UROH_LightEmitterComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UROH_LightEmitterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float angleBetweenRays = 360.0f / RaysCount;
	const float angleInRads = FMath::DegreesToRadians(angleBetweenRays);

	const FVector startPosition = GetOwner()->GetActorLocation();

	for (int32 i = 0; i < RaysCount; i++)
	{
		const float angle = i * angleInRads;
		const FVector endPosition = startPosition +
			FVector(FMath::Cos(angle), 0.0f, FMath::Sin(angle)) * LightRaduis;

		FHitResult outHit;

		const bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(),
			startPosition,
			endPosition,
			RaySphereRaduis,
			ObjectTypesArray,
			false,
			{ GetOwner() },
			EDrawDebugTrace::ForOneFrame,
			outHit,
			true
		);

		if (hit)
		{
			if (IROH_LightReactableInterface* lightReactable =
				Cast<IROH_LightReactableInterface>(outHit.HitObjectHandle.GetManagingActor()))
			{
				lightReactable->ReactToLight(LightRaduis - outHit.Distance);
			}
		}
	}
}

