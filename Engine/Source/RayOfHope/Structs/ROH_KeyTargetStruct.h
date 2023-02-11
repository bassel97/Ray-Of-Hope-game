// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "ROH_KeyTargetStruct.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FROH_KeyTargetStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<class AROH_KeyTargetParent> Target;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AROH_KeyTargetConnector> Connector;
};
