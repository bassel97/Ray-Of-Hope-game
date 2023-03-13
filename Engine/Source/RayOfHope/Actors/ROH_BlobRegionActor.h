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
	virtual void EditIndividualBlobs();
#endif

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector BlobBoxSize = FVector(1.0f);

	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 XAxisnumber = 1;
	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 YAxisnumber = 1;
	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ZAxisnumber = 1;

	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D RandomScale = FVector2D(1.0f, 1.0f);

	UPROPERTY(Category = BlobRegion, EditAnywhere, BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float CollapseToCenterAmount = 0.0f;

	UPROPERTY(Category = BlobRegionBlob, EditAnywhere, BlueprintReadOnly,	meta = (AllowPrivateAccess = "true"))
	FVector2D BlobMinMaxLightReactThresholds = FVector2D(0.0f, 1000.0f);;

	UPROPERTY(Category = BlobRegionBlob, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BlobLightReactionSpeed = 10.0f;

	UPROPERTY(Category = BlobRegion, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AROH_BlobActor> BlobActor;

	UPROPERTY(Category = BlobRegion, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class AROH_BlobActor>> BlobsArray;

	UPROPERTY(Category = Blob, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BoxCollider;

};
