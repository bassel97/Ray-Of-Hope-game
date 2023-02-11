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
	AROH_KeyTargetParent() {}

	virtual void Tick(float DeltaTime) override {}

	virtual void OpenTarget() PURE_VIRTUAL(AROH_KeyTargetParent::OpenTarget, );
	virtual void CloseTarget() PURE_VIRTUAL(AROH_KeyTargetParent::CloseTarget, );

	virtual FVector GetKeyTargetLineOriginLocation() { return KeyTargetLineOrigin->GetComponentLocation(); }


protected:
	virtual void BeginPlay() override {}

	virtual void CreateKeyTargetComponent();


protected:
	// This is a visual representation to where the line should begin
	UPROPERTY(Category = KeyTarget, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> KeyTargetLineOrigin;


private:

};
