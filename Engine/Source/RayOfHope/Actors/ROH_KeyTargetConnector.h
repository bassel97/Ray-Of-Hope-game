// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROH_KeyTargetConnector.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_KeyTargetConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	AROH_KeyTargetConnector();

	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void SetStartEndPoints(FVector keyLocation, FVector targetLocation);

	UFUNCTION(BlueprintImplementableEvent, Category = DoorTarget)
	void OnOpenTarget();

	UFUNCTION(BlueprintImplementableEvent, Category = DoorTarget)
	void OnCloseTarget();

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(Category = KeyTargetConnector, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USplineComponent> SplineComponent;

	UPROPERTY(Category = KeyTargetConnector, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMesh> SplineMesh;

	UPROPERTY()
	TArray<TObjectPtr<class USplineMeshComponent>> SplineMeshComponents;

	UPROPERTY(Category = KeyTargetConnector, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> SplineMaterial = nullptr;

	TObjectPtr<UMaterialInstanceDynamic> SplineDynamicMaterial = nullptr;

	UPROPERTY(Category = KeyTargetConnector, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bDeletePrevMeshes = false;
};
