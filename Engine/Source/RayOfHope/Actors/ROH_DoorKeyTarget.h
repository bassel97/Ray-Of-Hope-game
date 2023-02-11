// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "ROH_KeyTargetParent.h"
#include "ROH_DoorKeyTarget.generated.h"

/**
 * 
 */
UCLASS()
class RAYOFHOPE_API AROH_DoorKeyTarget : public AROH_KeyTargetParent
{
	GENERATED_BODY()
	
public:
	AROH_DoorKeyTarget();

	virtual void BeginPlay() override;

	virtual void OpenTarget() override;
	virtual void CloseTarget() override;

private:

	UPROPERTY(Category = Key, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> DoorStaticMesh;
};
