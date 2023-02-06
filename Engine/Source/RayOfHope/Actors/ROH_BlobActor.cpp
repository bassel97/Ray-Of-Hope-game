// Copyright di-tri.


#include "ROH_BlobActor.h"

AROH_BlobActor::AROH_BlobActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AROH_BlobActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AROH_BlobActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	//FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	Super::PostEditChangeProperty(e);
}

void AROH_BlobActor::EditBlobBox()
{

}
#endif

void AROH_BlobActor::BeginPlay()
{
	Super::BeginPlay();
	
}