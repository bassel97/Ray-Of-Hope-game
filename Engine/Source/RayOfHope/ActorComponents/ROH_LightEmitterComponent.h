// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROH_LightEmitterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAYOFHOPE_API UROH_LightEmitterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UROH_LightEmitterComponent();
	
	void SetRaduis(float raduis);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:	
	virtual void BeginPlay() override;


private:
	UPROPERTY(Category = LightEmitter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LightRaduis = 600.0f;

	UPROPERTY(Category = LightEmitter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RaySphereRaduis = 10.0f;

	UPROPERTY(Category = LightEmitter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 RaysCount = 120;

	UPROPERTY(Category = LightEmitter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray = TArray<TEnumAsByte<EObjectTypeQuery>>();

};
