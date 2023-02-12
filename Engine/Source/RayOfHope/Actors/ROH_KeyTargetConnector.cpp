// Copyright di-tri.


#include "ROH_KeyTargetConnector.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

AROH_KeyTargetConnector::AROH_KeyTargetConnector()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = SplineComponent;

}

void AROH_KeyTargetConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AROH_KeyTargetConnector::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(USplineMeshComponent::StaticClass());

		if (SplineMesh != nullptr)
		{
			SplineMesh->SetupAttachment(SplineComponent);
			SplineMesh->SetForwardAxis(ESplineMeshAxis::Z);

			SplineMesh->SetStartAndEnd(
				SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World),
				SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World),
				SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World),
				SplineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World));
		}
	}
}

void AROH_KeyTargetConnector::SetStartEndPoints(
	FVector keyLocation,
	FVector targetLocation)
{
	SplineComponent->SetSplinePoints({ keyLocation, targetLocation }, ESplineCoordinateSpace::World);
}

void AROH_KeyTargetConnector::BeginPlay()
{
	Super::BeginPlay();
	
}
