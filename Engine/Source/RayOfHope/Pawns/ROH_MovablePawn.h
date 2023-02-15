// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ROH_MovablePawn.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_MovablePawn : public APawn
{
	GENERATED_BODY()

public:
	AROH_MovablePawn();

	virtual void Tick(float DeltaTime) override;

	bool CanMoveRight() const;
	bool CanMoveLeft() const;

protected:
	virtual void BeginPlay() override;

private:
	bool CheckSensor(float sign) const;

private:
	UPROPERTY(Category = Movable, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector SensorOffset = FVector();

	UPROPERTY(Category = Movable, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SesorLength = 0.0f;

	UPROPERTY(Category = Movable, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> SensorTypesArray = TArray<TEnumAsByte<EObjectTypeQuery>>();

};
