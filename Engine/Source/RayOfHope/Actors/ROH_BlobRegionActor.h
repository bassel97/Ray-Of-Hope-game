// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROH_BlobRegionActor.generated.h"

UCLASS()
class RAYOFHOPE_API AROH_BlobRegionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AROH_BlobRegionActor();

	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void EditBlobBox();
#endif

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector BlobBoxSize = FVector(1.0f);

};
