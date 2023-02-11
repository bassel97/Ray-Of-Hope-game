// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayOfHope/Interfaces/ROH_LightReactableInterface.h"
#include "RayOfHope/Structs/ROH_KeyTargetStruct.h"
#include "ROH_KeyInteractableActor.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_KeyInteractableActor : public AActor, public IROH_LightReactableInterface
{
	GENERATED_BODY()
	
public:	
	AROH_KeyInteractableActor();

	virtual void Tick(float DeltaTime) override;

	// Functions overriding for light reaction Interface
	virtual void ResetInteractionWithLight() override;
	virtual void ReactToLight(float lightDistance) override;

	UFUNCTION()
	void OnKeyOverlapBegin(
		class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnKeyOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void SetUpKeyTargets();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;
	virtual void InteractWithTargets(bool isOpening);

	bool bShouldOpenByLight = false;
	bool bShouldOpenByLightPrevious = false;
	bool bShouldOpenByCollision = false;

private:
	UPROPERTY(Category = KeyInteractable, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FROH_KeyTargetStruct> KeyTargets;

	UPROPERTY(Category = Key, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bCanInteractWithLight = false;

	UPROPERTY(Category = Key, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LightInteractionThreshold = 0.0f;

	UPROPERTY(Category = Key, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bCanInteractWithDynamicObjects = false;


	UPROPERTY(Category = Key, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> KeyStaticMesh;

	UPROPERTY(Category = Key, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> KeyBoxCollider;

	// This is a visual representation to where the line should begin
	UPROPERTY(Category = Key, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> KeyTargetLineOrigin;

};