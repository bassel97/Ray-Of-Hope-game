// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ROH_BoyCharacter.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_BoyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AROH_BoyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void UpdateCameraOptions();

	// Input Functions:
	void BoyTryClimb();
	void BoyTryJumpDown();

	void BoyStartPush();
	void BoyEndPush();

	void HopeMoveHorizontal(float axisValue);
	void HopeMoveVertical(float axisValue);
	void BoyMoveHorizontal(float axisValue);

	UFUNCTION(BlueprintCallable, Category = Boy)
	bool IsBoyJumping() const {	return bIsJumpingRight || bIsJumpingLeft; }

	UFUNCTION(BlueprintCallable, Category = Boy)
	bool IsBoyJumpingDown() const { return bIsJumpingDownRight || bIsJumpingDownLeft; }

	UFUNCTION(BlueprintCallable, Category = Boy)
	bool IsBoyPushingPulling() const { return bIsPushingPulling; }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;

	void UpdateHeight();

	//TODO: this function should get the sign and a refrence out to the struct
	void UpdateSensor(float sign);

protected:
	class AROH_HopePawn* CreatedHopeRefrence = nullptr;
	
	// Boy movement variables**************************************
	float HopeHorizontalInput = 0.0f;
	float HopeVerticalInput = 0.0f;
	float BoyHorizontalInput = 0.0f;

	bool bIsJumpingRight = false;
	bool bIsJumpingLeft = false;

	bool bIsJumpingDownRight = false;
	bool bIsJumpingDownLeft = false;

	bool bIsPushingPulling = false;
	FVector CapturedPushObjectOffset = FVector();

	//TODO: Turn into struct
	bool bCanMoveRight = false;
	bool bCanJumpRight = false;
	bool bCanPushBoxRight = false;
	bool bCanPushBoxLeft = false;
	FVector JumpTargetRight = FVector();
	AActor* ActorToPush = nullptr;

	bool bCanMoveLeft = false;
	//bool bCanPushBoxLeft = false;
	bool bCanJumpLeft = false;
	FVector JumpTargetLeft = FVector();
	//AActor* ActorToPushLeft = nullptr;
	/***********************************************************/

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BoyHeight = 140.0f;

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector BoyMeshOffset = FVector(0, 0, 2.0f);

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector SpringArmOffset = FVector(0, 0, 100.0f);

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator SpringArmRotator = FRotator();

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpringLength = 600.0f;

	UPROPERTY(Category = Boy, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AROH_HopePawn> HopePawnToSpawn = nullptr;


	UPROPERTY(Category = BoyNavigation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RayCastPosZOffset = 10.0f;

	UPROPERTY(Category = BoyNavigation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RayCastNegZOffset = 80.0f;

	UPROPERTY(Category = BoyNavigation, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray = TArray<TEnumAsByte<EObjectTypeQuery>>();


private:
	UPROPERTY(Category = Boy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(Category = Boy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

};
