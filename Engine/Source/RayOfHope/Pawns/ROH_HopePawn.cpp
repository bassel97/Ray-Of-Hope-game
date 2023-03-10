// Copyright di-tri.


#include "ROH_HopePawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "RayOfHope/ActorComponents/ROH_LightEmitterComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Engine/EngineTypes.h"

AROH_HopePawn::AROH_HopePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hope Collision"));
	SphereComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	SphereComponent->CanCharacterStepUpOn = ECB_No;
	SphereComponent->SetShouldUpdatePhysicsVolume(true);
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->bDynamicObstacle = true;
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Hope Mesh"));
	if (StaticMeshComponent)
	{
		StaticMeshComponent->AlwaysLoadOnClient = true;
		StaticMeshComponent->AlwaysLoadOnServer = true;
		StaticMeshComponent->bOwnerNoSee = false;
		StaticMeshComponent->bCastDynamicShadow = false;
		StaticMeshComponent->bAffectDynamicIndirectLighting = true;
		StaticMeshComponent->SetupAttachment(SphereComponent);
	}

	PointLightComponent = CreateOptionalDefaultSubobject<UPointLightComponent>(TEXT("Hope Light"));
	if (PointLightComponent)
	{
		PointLightComponent->SetupAttachment(SphereComponent);
		PointLightComponent->SetSourceRadius(0.0f);
	}

	HopeLightSphereEffect = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Hope Light Sphere Effect"));
	if (HopeLightSphereEffect)
	{
		HopeLightSphereEffect->SetupAttachment(SphereComponent);
	}

	MovementComponent = CreateOptionalDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement Component"));
	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = SphereComponent;
	}

	LightEmitterComponent = CreateOptionalDefaultSubobject<UROH_LightEmitterComponent>(TEXT("Light Emitter Component"));
	if (LightEmitterComponent)
	{
		LightEmitterComponent->SetRaduis(HopePointLightRaduis);
	}

	UpdateScale();
}

void AROH_HopePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScale();

	TimePassed += DeltaTime;

	const FVector2D frequency = FVector2D(
		FMath::Lerp(HopeFreqMinMax.X, HopeFreqMinMax.Y, HopeStressValue),
		FMath::Lerp(HopeFreqMinMax.X, HopeFreqMinMax.Y, HopeStressValue)
	);

	const float amplitude = HopeLiveRaduis * ((frequency.X + frequency.Y) / 2.0f);

	const FVector aliveEffectDelta = FVector(
		FMath::Sin(TimePassed * (frequency.X + RandomFrequencyOffset.X)) * amplitude,
		0.0f,
		FMath::Cos(TimePassed * (frequency.Y + RandomFrequencyOffset.Y)) * amplitude
	);

	const FVector playerInput =
		FVector(HopePlayerInput.X, 0.0f, HopePlayerInput.Y) * HopeMoveSpeed;

	AddMovementInput(aliveEffectDelta + playerInput);
}

void AROH_HopePawn::SetPlayerInput(FVector2D playerInput)
{
	HopePlayerInput = playerInput;
}

void AROH_HopePawn::SetStressValue(float stressValue)
{
	HopeStressValue = stressValue;

	RandomFrequencyOffset = FMath::RandPointInCircle(1.0f);
}

#if WITH_EDITOR
void AROH_HopePawn::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_HopePawn, HopeScale)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_HopePawn, HopePointLightRaduis))
	{
		UpdateScale();
	}
	Super::PostEditChangeProperty(e);
}
#endif

void AROH_HopePawn::BeginPlay()
{
	Super::BeginPlay();

	RandomFrequencyOffset = FMath::RandPointInCircle(1.0f);

	HopeAlivePositionPrevOffset = FVector(0.0f);
}

void AROH_HopePawn::UpdateScale()
{
	SphereComponent->InitSphereRadius(100.0f * HopeScale);

	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetWorldScale3D(FVector(HopeScale));
	}
	if (HopeLightSphereEffect)
	{
		// The Raduis of sphere mesh is 160.0f
		HopeLightSphereEffect->SetWorldScale3D(FVector(HopePointLightRaduis / 160.0f));
	}
	if (PointLightComponent)
	{
		PointLightComponent->SetAttenuationRadius(HopePointLightRaduis);
	}
	if (LightEmitterComponent)
	{
		LightEmitterComponent->SetRaduis(HopePointLightRaduis);
	}
}