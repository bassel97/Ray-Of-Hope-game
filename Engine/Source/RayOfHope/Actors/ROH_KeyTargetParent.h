// Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROH_KeyTargetParent.generated.h"

UCLASS(Abstract)
class RAYOFHOPE_API AROH_KeyTargetParent : public AActor
{
	GENERATED_BODY()
	
public:	
	AROH_KeyTargetParent();

	virtual void Tick(float DeltaTime) override;

	virtual void OpenTarget()
	{
		OnOpenTarget();
	}

	virtual void CloseTarget()
	{
		OnCloseTarget();
	}

	virtual FVector GetKeyTargetLineOriginLocation() { return KeyTargetLineOrigin->GetComponentLocation(); }

	UFUNCTION(BlueprintImplementableEvent, Category = DoorTarget)
		void OnOpenTarget();

	UFUNCTION(BlueprintImplementableEvent, Category = DoorTarget)
		void OnCloseTarget();

protected:
	virtual void BeginPlay() override;

	//virtual void CreateKeyTargetComponent();


protected:
	// This is a visual representation to where the line should begin
	UPROPERTY(Category = KeyTarget, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> KeyTargetLineOrigin;


private:

	UPROPERTY(Category = Key, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMesh;
};
