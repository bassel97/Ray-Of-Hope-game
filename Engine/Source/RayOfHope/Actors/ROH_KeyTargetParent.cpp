// Copyright di-tri.

#include "ROH_KeyTargetParent.h"

AROH_KeyTargetParent::AROH_KeyTargetParent()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	StaticMesh->CanCharacterStepUpOn = ECB_No;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	RootComponent = StaticMesh;

	KeyTargetLineOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("Key Target Line Origin"));
	if (KeyTargetLineOrigin)
	{
		KeyTargetLineOrigin->SetupAttachment(RootComponent);
	}
}

void AROH_KeyTargetParent::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
}

void AROH_KeyTargetParent::BeginPlay()
{
	Super::BeginPlay();

}