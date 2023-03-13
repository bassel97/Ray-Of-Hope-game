// Copyright di-tri.


#include "ROH_MovablePawn.h"
#include "Kismet/KismetSystemLibrary.h"

AROH_MovablePawn::AROH_MovablePawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AROH_MovablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AROH_MovablePawn::CanMoveRight() const
{
	return !CheckSensor(1.0f);
}

bool AROH_MovablePawn::CanMoveLeft() const
{
	return !CheckSensor(-1.0f);
}

void AROH_MovablePawn::BeginPlay()
{
	Super::BeginPlay();	
}

bool AROH_MovablePawn::CheckSensor(float sign) const
{
	FHitResult outHitMovingSensor;
	const bool hitMovingSensor = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		GetActorLocation() + SensorOffset,
		GetActorLocation() + SensorOffset + FVector(sign * SesorLength, 0.0f, 0.0f),
		10.0f,
		SensorTypesArray,
		false,
		{ },
		EDrawDebugTrace::ForOneFrame,
		outHitMovingSensor,
		true
	);
	return hitMovingSensor;
}