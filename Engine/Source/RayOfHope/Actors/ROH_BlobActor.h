// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROH_BlobActor.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_BlobActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AROH_BlobActor();

	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void EditBlobBox();
#endif

protected:
	virtual void BeginPlay() override;

protected:

};
