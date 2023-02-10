// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayOfHope/Interfaces/ROH_LightReactableInterface.h"
#include "ROH_BlobActor.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_BlobActor : public AActor, public IROH_LightReactableInterface
{
	GENERATED_BODY()
	
public:	
	AROH_BlobActor();

	virtual void Tick(float DeltaTime) override;

	void SetBlobRaduis(float raduis);
	void SetLightReactionSpeed(float lightReactionSpeed);
	void SetMinMaxLightReactThresholds(FVector2D minMaxLightReactThresholds);

	// Functions overriding for light reaction Interface
	virtual void ResetInteractionWithLight() override;
	virtual void ReactToLight(float lightDistance) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;

	FVector TargetBlobScale = FVector(1.0f);

private:
	UPROPERTY(Category = Blob, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BlobRaduis = 12.0f;

	UPROPERTY(Category = Blob, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(Category = Blob, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BoxDynamicCollider;
	ECollisionEnabled::Type BoxColliderType = ECollisionEnabled::NoCollision;

	UPROPERTY(Category = Blob, EditAnywhere, BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float BoxDynamicLightThreshold = 0.75f;

	UPROPERTY(Category = Blob, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(Category = LightReactable, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LightReactionSpeed = 10.0f;

	UPROPERTY(Category = LightReactable, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D MinMaxLightReactThresholds = FVector2D(0.0f, 1000.0f);
};
