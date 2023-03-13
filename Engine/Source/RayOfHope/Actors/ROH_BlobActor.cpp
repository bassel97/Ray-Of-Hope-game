// Copyright di-tri.


#include "ROH_BlobActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RayOfHope/Characters/ROH_BoyCharacter.h"

AROH_BlobActor::AROH_BlobActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Blob Collision"));
	SphereComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	SphereComponent->CanCharacterStepUpOn = ECB_No;
	SphereComponent->SetShouldUpdatePhysicsVolume(true);
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->bDynamicObstacle = true;
	SphereComponent->SetSphereRadius(BlobRaduis);
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Blob Mesh"));
	if (StaticMeshComponent)
	{
		StaticMeshComponent->bOwnerNoSee = false;
		StaticMeshComponent->bCastDynamicShadow = false;
		StaticMeshComponent->bAffectDynamicIndirectLighting = true;
		StaticMeshComponent->bUseDefaultCollision = false;
		StaticMeshComponent->SetWorldScale3D(FVector(BlobRaduis / 160.0f));
		StaticMeshComponent->SetupAttachment(SphereComponent);
	}

	BoxDynamicCollider = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Blob Box Dynamic Collider"));
	if (BoxDynamicCollider)
	{
		BoxDynamicCollider->SetBoxExtent(FVector(BlobRaduis));
		BoxDynamicCollider->OnComponentBeginOverlap.AddDynamic(this, &AROH_BlobActor::OnOverlapBegin);
		BoxDynamicCollider->OnComponentEndOverlap.AddDynamic(this, &AROH_BlobActor::OnOverlapEnd);       
		BoxDynamicCollider->SetupAttachment(SphereComponent);
	}
}

void AROH_BlobActor::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

	const FVector scale = FMath::Lerp(GetActorScale(), TargetBlobScale, DeltaTime * LightReactionSpeed);
	SetActorScale3D(scale);
}

void AROH_BlobActor::SetBlobRaduis(float raduis)
{
	BlobRaduis = raduis;

	SphereComponent->SetSphereRadius(BlobRaduis);
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetWorldScale3D(FVector(BlobRaduis / 160.0f));
		BoxDynamicCollider->SetBoxExtent(FVector(BlobRaduis));
	}
}

void AROH_BlobActor::SetLightReactionSpeed(float lightReactionSpeed)
{
	LightReactionSpeed = lightReactionSpeed;
}

void AROH_BlobActor::SetMinMaxLightReactThresholds(FVector2D minMaxLightReactThresholds)
{
	MinMaxLightReactThresholds = MinMaxLightReactThresholds;
}

void AROH_BlobActor::ResetInteractionWithLight()
{
	IROH_LightReactableInterface::ResetInteractionWithLight();

	TargetBlobScale = FVector(1.0f);
}

void AROH_BlobActor::ReactToLight(float lightDistance)
{
	IROH_LightReactableInterface::ReactToLight(lightDistance);

	const float lightRecievedValue = FMath::Clamp(
		UKismetMathLibrary::NormalizeToRange(lightDistance, MinMaxLightReactThresholds.X, MinMaxLightReactThresholds.Y),
		0.0f, 0.8f);

	TargetBlobScale = FVector(1.0f - lightRecievedValue);

	if (lightRecievedValue > BoxDynamicLightThreshold)
	{
		BoxDynamicCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		BoxDynamicCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
	}
}

void AROH_BlobActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AROH_BoyCharacter* boyCharacter = Cast<AROH_BoyCharacter>(OtherActor))
	{
		OnPlayerEnterblob(boyCharacter);
	}
}

void AROH_BlobActor::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AROH_BoyCharacter* boyCharacter = Cast<AROH_BoyCharacter>(OtherActor))
	{
		OnPlayerExitblob(boyCharacter);
	}
}

#if WITH_EDITOR
void AROH_BlobActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BlobActor, BlobRaduis))
	{
		SetBlobRaduis(BlobRaduis);
	}
	Super::PostEditChangeProperty(e);
}
#endif

void AROH_BlobActor::BeginPlay()
{
	AActor::BeginPlay();
}