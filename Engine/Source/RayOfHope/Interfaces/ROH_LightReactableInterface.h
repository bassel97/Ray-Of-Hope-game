// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ROH_LightReactableInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UROH_LightReactableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IROH_LightReactableInterface
{
	GENERATED_BODY()

public:
	virtual void ResetInteractionWithLight();
	virtual void ReactToLight(float lightDistance);

protected:
	float TotalInteraction = 0.0f;

};