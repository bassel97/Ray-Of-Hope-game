// Copyright di-tri.

#include "ROH_DoorKeyTarget.h"


AROH_DoorKeyTarget::AROH_DoorKeyTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	DoorStaticMesh->CanCharacterStepUpOn = ECB_No;
	DoorStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorStaticMesh->SetCollisionObjectType(ECC_WorldStatic);
	RootComponent = DoorStaticMesh;

	CreateKeyTargetComponent();
}

void AROH_DoorKeyTarget::BeginPlay()
{
	Super::BeginPlay();

}


void AROH_DoorKeyTarget::OpenTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, "OpenTarget()");
}

void AROH_DoorKeyTarget::CloseTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, "CloseTarget()");
}