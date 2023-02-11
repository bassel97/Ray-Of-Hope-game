// Copyright di-tri.

#include "ROH_KeyTargetParent.h"

void AROH_KeyTargetParent::CreateKeyTargetComponent()
{
	KeyTargetLineOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("Key Target Line Origin"));
	if (KeyTargetLineOrigin)
	{
		KeyTargetLineOrigin->SetupAttachment(RootComponent);
	}
}