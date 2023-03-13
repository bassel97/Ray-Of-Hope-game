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

	TestTime += DeltaTime;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(DeltaTime)
	);

	SplineDynamicMaterial->SetScalarParameterValue("TimeParameter", TestTime);
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

	SplineMeshComponents.Empty();

	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* splineMeshComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		if (splineMeshComp != nullptr)
		{
			SplineMeshComponents.Add(splineMeshComp);

			splineMeshComp->SetStaticMesh(SplineMesh);
			splineMeshComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			splineMeshComp->SetForwardAxis(ESplineMeshAxis::Z);
			splineMeshComp->RegisterComponentWithWorld(GetWorld());
			splineMeshComp->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

			splineMeshComp->SetStartAndEnd(
				SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local),
				SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local),
				SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local),
				SplineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local), true);

			/*if (SplineDynamicMaterial != nullptr)
			{
				splineMeshComp->SetMaterial(0, SplineDynamicMaterial.Get());
			}*/
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
	SplineComponent->SetLocationAtSplinePoint(0, keyLocation, ESplineCoordinateSpace::Local);
	SplineComponent->SetLocationAtSplinePoint(
		SplineComponent->GetNumberOfSplinePoints() - 1, targetLocation, ESplineCoordinateSpace::Local);
	//}
}

void AROH_KeyTargetConnector::BeginPlay()
{
	Super::BeginPlay();
	
	SplineDynamicMaterial = UMaterialInstanceDynamic::Create(SplineMaterial, this);
	for (TObjectPtr<USplineMeshComponent> splineMeshCompoent : SplineMeshComponents)
	{
		splineMeshCompoent->SetMaterial(0, SplineDynamicMaterial.Get());
	}

	//SplineDynamicMaterial->SetScalarParameterValue("MyParameter", myFloatValue);
}
