// Copyright di-tri.


#include "ROH_BlobRegionActor.h"

AROH_BlobRegionActor::AROH_BlobRegionActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AROH_BlobRegionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AROH_BlobRegionActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobRegionActor, BlobBoxSize))
	{
		//gEngine->draw
	}
	Super::PostEditChangeProperty(e);
}

void AROH_BlobRegionActor::EditBlobBox()
{

}
#endif

void AROH_BlobRegionActor::BeginPlay()
{
	Super::BeginPlay();
	
}