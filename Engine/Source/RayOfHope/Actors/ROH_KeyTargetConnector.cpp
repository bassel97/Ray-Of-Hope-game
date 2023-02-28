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

	// Hack to delete splines in editing
	/*if (bDeletePrevMeshes)
	{
		for (USplineMeshComponent* splineComp : SplineMeshComponents)
		{
			splineComp->DestroyComponent();
		}
		SplineMeshComponents.Empty();
	}*/

	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* splineMeshComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		if (splineMeshComp != nullptr)
		{
			//SplineMeshComponents.Add(splineMeshComp);

			splineMeshComp->SetupAttachment(SplineComponent);
			splineMeshComp->SetForwardAxis(ESplineMeshAxis::Z);
			splineMeshComp->SetStaticMesh(SplineMesh);
			splineMeshComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			splineMeshComp->RegisterComponentWithWorld(GetWorld());

			splineMeshComp->SetStartAndEnd(
				SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World),
				SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World),
				SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World),
				SplineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World), true);
		}
	}
}

void AROH_KeyTargetConnector::SetStartEndPoints(
	FVector keyLocation,
	FVector targetLocation)
{
	//if (bDeletePrevMeshes)
	//{
	//SplineComponent->SetSplinePoints({ keyLocation, targetLocation }, ESplineCoordinateSpace::World);
	SplineComponent->SetLocationAtSplinePoint(0, keyLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetLocationAtSplinePoint(
		SplineComponent->GetNumberOfSplinePoints() - 1, targetLocation, ESplineCoordinateSpace::World);
	//}
}

void AROH_KeyTargetConnector::BeginPlay()
{
	Super::BeginPlay();
	
}
