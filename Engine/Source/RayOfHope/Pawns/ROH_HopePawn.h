// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ROH_HopePawn.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_HopePawn : public APawn
{
	GENERATED_BODY()

public:
	AROH_HopePawn();

	virtual void Tick(float DeltaTime) override;

	void UpdateHopeScale(const float value) { HopeScale = value; }
	void UpdateHopePointLightRaduis(const float value) { HopePointLightRaduis = value; }

	UFUNCTION(BlueprintCallable, Category = Hope)
	void SetPlayerInput(FVector2D playerInput);

	UFUNCTION(BlueprintCallable, Category = Hope)
	void SetStressValue(float stressValue);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:


protected:
	virtual void BeginPlay() override;

	/** Uses HopeScale to updat HopeScale*/
	void UpdateScale();

protected:

	// The values passed by the player input
	FVector2D HopePlayerInput = FVector2D(0.0f);

	FVector HopeAlivePositionOffset = FVector(0.0f);
	FVector HopeAlivePositionPrevOffset = FVector(0.0f);

	FVector2D HopeAliveFrequency = FVector2D();
	FVector2D RandomFrequencyOffset = FVector2D();


private:

	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPointLightComponent> PointLightComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFloatingPawnMovement> MovementComponent;

	/**
	* 0 -> 1 float
	* expresses the scale of hope
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeScale = 0.15f;

	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopePointLightRaduis = 600.0f;

	/**The raduis in which hope moves.*/
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeLiveRaduis = 0.025f;

	/**The stress is how fast it animates.*/
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite,
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float HopeStressValue = 0.0f;
	
	/**Frequency min (xValue) and max (yValue) of moving.*/
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D HopeFreqMinMax = FVector2D(1.0f, 20.0f);
	
	/**Hope move speed from input.*/
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeMoveSpeed = 60.0f;

	/** Time passed since the start*/
	float TimePassed = 0.0f;

};
