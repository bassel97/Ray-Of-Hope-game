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
	// Sets default values for this actor's properties
	AROH_HopePawn();

	// Called every frame
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Uses HopeScale to updat HopeScale*/
	void UpdateScale();

	//void UpdateAliveHope();


protected:
	/**
	* The global refrence position of Hope
	* Edit for test
	*/
	//UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//FVector HopeGlobalPosition = FVector(0.0f);

	FVector2D HopePlayerInput = FVector2D(0.0f);

	/**
	* The position of Hope after the alive effect
	*/
	//UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector HopeAlivePositionOffset = FVector(0.0f);
	FVector HopeAlivePositionPrevOffset = FVector(0.0f);

	FVector2D HopeAliveFrequency = FVector2D();
	FVector2D RandomFrequencyOffset = FVector2D();



private:
	/** The CapsuleComponent being used for movement collision (by CharacterMovement).
	Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;

	/**
	 */
	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	/**
	 */
	UPROPERTY(Category = Hope, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPointLightComponent> PointLightComponent;


	/** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFloatingPawnMovement> MovementComponent;

	/**
	* 0 -> 1 float
	* expresses the scale of hope
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeScale = 0.15f;

	/**
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopePointLightRaduis = 600.0f;

	/**
	* The raduis in which hope moves.
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeLiveRaduis = 0.025f;

	/**
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite,
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float HopeStressValue = 0.0f;

	/**
	* xValue = time between 2 jumps at zero stress in seconds
	* yValue = time between 2 jumps at one stress in seconds
	 */
	//UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//FVector2D HopeTimeMinMax = FVector2D(1.0f, 0.1f);

	/**
	* Frequency min (xValue) and max (yValue) of moving.
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D HopeFreqMinMax = FVector2D(1.0f, 20.0f);

	
	/**
	* Hope move speed from input
	 */
	UPROPERTY(Category = Hope, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HopeMoveSpeed = 60.0f;

	/**
	* Alive timer hanle
	*/
	//struct FTimerHandle HopeAliveTimerHandle;
	//float HopeAliveLerpTimer = 0.0f;
	//float TimeTillNextJump = 0.0f;

	/** Time passed since the start*/
	float TimePassed = 0.0f;

};
