// Copyright di-tri.


#include "ROH_LightReactableInterface.h"

void IROH_LightReactableInterface::ResetInteractionWithLight()
{
	TotalInteraction = 0.0f;
}


void IROH_LightReactableInterface::ReactToLight(float lightDistance)
{
	TotalInteraction += lightDistance;
}