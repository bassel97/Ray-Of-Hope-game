// Copyright di-tri.

#include "ROH_BoyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AROH_BoyCharacter::AROH_BoyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	if (SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(RootComponent);
	}
	CameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
	}
}

void AROH_BoyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AROH_BoyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AROH_BoyCharacter::UpdateCameraOptions()
{
	if (SpringArmComponent)
	{
		SpringArmComponent->TargetArmLength = SpringLength;
		SpringArmComponent->SocketOffset = SpringArmOffset;
		SpringArmComponent->SetRelativeRotation(SpringArmRotator);
	}
}

#if WITH_EDITOR
void AROH_BoyCharacter::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.MemberProperty->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BoyCharacter, BoyHeight)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BoyCharacter, BoyMeshOffset))
	{
		UpdateHeight();
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BoyCharacter, SpringArmOffset)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BoyCharacter, SpringLength)
		|| PropertyName == GET_MEMBER_NAME_CHECKED(AROH_BoyCharacter, SpringArmRotator))
	{
		UpdateCameraOptions();
	}
	Super::PostEditChangeProperty(e);
}
#endif

void AROH_BoyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateHeight();
	UpdateCameraOptions();
}

void AROH_BoyCharacter::UpdateHeight()
{
	const float halfBoyHeight = BoyHeight * 0.5f;
	if (UCapsuleComponent* capsuleComponent = GetCapsuleComponent())
	{
		capsuleComponent->SetCapsuleHalfHeight(halfBoyHeight);
	}
	if (USkeletalMeshComponent* characterMesh = GetMesh())
	{
		characterMesh->SetRelativeLocation(FVector(0, 0, -halfBoyHeight) + BoyMeshOffset);
	}
	if (USkeletalMeshComponent* characterMesh = GetMesh())
	{
		characterMesh->SetRelativeRotation(FRotator(0, 270, 0));
	}
}