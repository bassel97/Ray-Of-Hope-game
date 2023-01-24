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

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;

	void UpdateHeight();

protected:
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

private:
	UPROPERTY(Category = Boy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(Category = Boy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;


};
