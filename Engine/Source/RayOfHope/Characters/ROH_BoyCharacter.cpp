// Copyright di-tri.

#include "ROH_BoyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "RayOfHope/Pawns/ROH_HopePawn.h"
#include "RayOfHope/Pawns/ROH_MovablePawn.h"

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

	// Update Hope position
	if (CreatedHopeRefrence)
	{
		const FVector2D hopeDirection = FVector2D(HopeHorizontalInput, HopeVerticalInput);
		CreatedHopeRefrence->SetPlayerInput(hopeDirection);
	}

	// Update Boy's navigation sensors
	UpdateSensor(1.0f);
	UpdateSensor(-1.0f);

	// Boy Jumping up
	/*if (!GetMovementComponent()->IsMovingOnGround())
	{
		if (bIsJumpingRight)
		{
			AddMovementInput(FVector(1.0, 0.0f, 0.0f));
		}
		if (bIsJumpingLeft)
		{
			AddMovementInput(FVector(-1.0f, 0.0f, 0.0f));
		}
	}*/
	//else
	/*{
		if (bIsJumpingRight)
		{
			bIsJumpingRight = false;
		}
		if (bIsJumpingLeft)
		{
			bIsJumpingLeft = false;
		}
	}*/

	// Boy Jumping Down
	//if (bIsJumpingDownRight)
	{
		if (!bCanMoveRight)
		{
			//AddMovementInput(FVector(1.0f, 0.0f, 0.0f));
		}
		else
		{
			//bIsJumpingDownRight = false;
		}
	}
	//if (bIsJumpingDownLeft)
	{
		if (!bCanMoveLeft)
		{
			//AddMovementInput(FVector(-1.0f, 0.0f, 0.0f));
		}
		else
		{
			//bIsJumpingDownLeft = false;
		}
	}

	/*if (bIsPushingPulling)
	{
		if (APawn* actorAsPawn = Cast<APawn>(ActorToPush))
		{
			actorAsPawn->AddMovementInput(
				FVector(BoyHorizontalInput, 0, 0)
			);// = GetCharacterMovement()->getvelocity;

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FVector(BoyHorizontalInput, 0, 0).ToString());
		}
	}*/
}

void AROH_BoyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("BoyClimb", IE_Pressed, this, &AROH_BoyCharacter::BoyTryClimb);
	PlayerInputComponent->BindAction("BoyJumpDown", IE_Pressed, this, &AROH_BoyCharacter::BoyTryJumpDown);

	PlayerInputComponent->BindAction("BoyPush", IE_Pressed, this, &AROH_BoyCharacter::BoyStartPush);
	PlayerInputComponent->BindAction("BoyPush", IE_Released, this, &AROH_BoyCharacter::BoyEndPush);

	PlayerInputComponent->BindAxis("HopeMoveHorizontal", this, &AROH_BoyCharacter::HopeMoveHorizontal);
	PlayerInputComponent->BindAxis("HopeMoveVertical", this, &AROH_BoyCharacter::HopeMoveVertical);

	PlayerInputComponent->BindAxis("BoyMoveHorizontal", this, &AROH_BoyCharacter::BoyMoveHorizontal);
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

void AROH_BoyCharacter::BoyTryClimb()
{
	if (CanReactToInputMove() /*|| bIsJumpingDownRight || bIsJumpingDownLeft*/)
	{
		return;
	}

	if (bCanJumpRight && BoyHorizontalInput > 0.0f)
	{
		bIsJumpingRight = true;
		if (UCharacterMovementComponent* const movementComponent = GetCharacterMovement())
		{
			movementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
			GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
			const float animTime = PlayAnimMontage(ClimbBoxAnimMontage.Get());
			GetWorld()->GetTimerManager().SetTimer(
				AnimMontageEndTimerHandle, this, &AROH_BoyCharacter::OnAnimationMontageEnd, animTime, false);
		}
		//Jump();
	}

	if (bCanJumpLeft && BoyHorizontalInput < 0.0f)
	{
		bIsJumpingLeft = true;
		if (UCharacterMovementComponent* const movementComponent = GetCharacterMovement())
		{
			movementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
			GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
			const float animTime = PlayAnimMontage(ClimbBoxAnimMontage.Get());
			GetWorld()->GetTimerManager().SetTimer(
				AnimMontageEndTimerHandle, this, &AROH_BoyCharacter::OnAnimationMontageEnd, animTime, false);
		}
		//Jump();
	}
}
void AROH_BoyCharacter::BoyTryJumpDown()
{
	if (CanReactToInputMove() /*|| bIsJumpingDownRight || bIsJumpingDownLeft*/)
	{
		return;
	}

	/*if (!bCanMoveRight)
	{
		bIsJumpingDownRight = true;
	}
	if (!bCanMoveLeft)
	{
		bIsJumpingDownLeft = true;
	}*/
}

void AROH_BoyCharacter::BoyStartPush()
{
	if (CanReactToInputMove() /*|| bIsJumpingDownRight || bIsJumpingDownLeft*/)
	{
		return;
	}

	if ((ActorToPush != nullptr) && (bCanPushBoxRight || bCanPushBoxLeft))
	{
		if (AROH_MovablePawn* movable = Cast<AROH_MovablePawn>(ActorToPush))
		{
			CurrentMovablePawn = movable;

			Crouch();
			if (UCharacterMovementComponent* const movementComponent = GetCharacterMovement())
			{
				movementComponent->bOrientRotationToMovement = false;
			}
			bIsPushingPulling = true;

			if (UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(ActorToPush->GetRootComponent()))
			{
				/*rootComp->SetCollisionResponseToChannel(
					ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore
				);*/
				rootComp->SetSimulatePhysics(false);
				ActorToPush->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				//if (APawn* actorAsPawn = Cast<APawn>(ActorToPush))
				//{
				//	actorAsPawn->AddMovementInput(
				//		FVector(BoyHorizontalInput, 0, 0)
				//	);// = GetCharacterMovement()->getvelocity;

				//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FVector(BoyHorizontalInput, 0, 0).ToString());
				//}
			}			
		}
	}		
}
void AROH_BoyCharacter::BoyEndPush()
{
	if (CanReactToInputMove() /*|| bIsJumpingDownRight || bIsJumpingDownLeft*/)
	{
		return;
	}

	if ((ActorToPush != nullptr) && bIsPushingPulling)
	{
		UnCrouch();
		bIsPushingPulling = false;
		CurrentMovablePawn = nullptr;

		if (UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(ActorToPush->GetRootComponent()))
		{
			rootComp->SetSimulatePhysics(true);
			//rootComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
			ActorToPush->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		
		if (UCharacterMovementComponent* const movementComponent = GetCharacterMovement())
		{
			movementComponent->bOrientRotationToMovement = true;
		}
	}
}

void AROH_BoyCharacter::HopeMoveHorizontal(float axisValue)
{
	HopeHorizontalInput = axisValue;
}
void AROH_BoyCharacter::HopeMoveVertical(float axisValue)
{
	HopeVerticalInput = axisValue;
}
void AROH_BoyCharacter::BoyMoveHorizontal(float axisValue)
{
	if (CanReactToInputMove() /*|| bIsJumpingDownRight || bIsJumpingDownLeft*/)
	{
		return;
	}

	BoyHorizontalInput = axisValue;

	if (axisValue > 0)
	{
		if (bCanMoveRight || (bIsPushingPulling && CurrentMovablePawn && CurrentMovablePawn->CanMoveRight()))
		{
			AddMovementInput(FVector(axisValue, 0.0f, 0.0f));
		}
	}

	if (axisValue < 0)
	{
		if (bCanMoveLeft || (bIsPushingPulling && CurrentMovablePawn && CurrentMovablePawn->CanMoveLeft()))
		{
			AddMovementInput(FVector(axisValue, 0.0f, 0.0f));
		}
	}
}

bool AROH_BoyCharacter::CanReactToInputMove() const
{
	return bIsJumpingRight || bIsJumpingLeft;
}

bool AROH_BoyCharacter::IsBoyJumpingDown() const
{
	return !GetMovementComponent()->IsMovingOnGround();
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

	if (bBoyCreateHope)
	{
		CreatedHopeRefrence = GetWorld()->SpawnActor<AROH_HopePawn>(
			HopePawnToSpawn, GetActorLocation() + HopeCreationOffset, GetActorRotation()
			);
	}
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

void AROH_BoyCharacter::UpdateSensor(float sign)
{
	FHitResult outHitMovingSensor;
	const bool hitMovingSensor = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		GetActorLocation() + MovingStoppingDistanceOffset,
		GetActorLocation() + MovingStoppingDistanceOffset + FVector(sign * MovingStoppingDistance, 0.0f, 0.0f),
		10.0f,
		ObjectTypesArray,
		false,
		{ },
		EDrawDebugTrace::ForOneFrame,
		outHitMovingSensor,
		true
	);
	if (hitMovingSensor)
	{
		if (sign > 0)
		{
			bCanMoveRight = false;
		}
		else
		{
			bCanMoveLeft = false;
		}
	}
	else
	{
		if (sign > 0)
		{
			bCanMoveRight = true;
		}
		else
		{
			bCanMoveLeft = true;
		}
	}

	//TODO: Replace with actual distances or calculate from cylinder raduis
	const FVector startPosition = GetActorLocation() + FVector(sign * MovingStoppingDistance, 0.0f, RayCastPosZOffset);
	const FVector endPosition = GetActorLocation() + FVector(sign * MovingStoppingDistance, 0.0f, -RayCastNegZOffset);

	FHitResult outHit;
	const bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		startPosition,
		endPosition,
		10.0f,
		ObjectTypesArray,
		false,
		{ },
		EDrawDebugTrace::ForOneFrame,
		outHit,
		true
	);

	const bool isFacingObject = (outHit.ImpactPoint - GetActorLocation()).Dot(GetActorForwardVector()) > 0.85f;
	const bool isObjectInfront = FMath::Abs(outHit.ImpactPoint.Z - endPosition.Z) > 25.0f;
	if (hit)
	{
		// right
		if (sign > 0)
		{
			if (isObjectInfront)
			{
				bCanJumpRight = true;
				JumpTargetRight = outHit.ImpactPoint + BoyHeight / 2.0f;
			}
			if (isObjectInfront && isFacingObject)
			{
				bCanPushBoxRight = true;
				ActorToPush = outHit.GetActor();
			}
			else
			{
				bCanPushBoxRight = false;
			}
		}
		// left
		else if (sign < 0)
		{
			if (isObjectInfront)
			{
				bCanJumpLeft = true;
				JumpTargetLeft = outHit.ImpactPoint + BoyHeight / 2.0f;
			}
			if (isObjectInfront && isFacingObject)
			{
				bCanPushBoxLeft = true;
				ActorToPush = outHit.GetActor();
			}
			else
			{
				bCanPushBoxLeft = false;
			}
		}
	}
	else
	{
		// right
		if (sign > 0)
		{
			if (isObjectInfront)
			{
				bCanJumpRight = false;
			}
			bCanPushBoxRight = false;
			if (!bCanPushBoxLeft)
			{
				ActorToPush = nullptr;
			}
		}
		// left
		else if (sign < 0)
		{
			if (isObjectInfront)
			{
				bCanJumpLeft = false;
			}
			bCanPushBoxLeft = false;
			if (!bCanPushBoxRight)
			{
				ActorToPush = nullptr;
			}
		}		
	}
}


void AROH_BoyCharacter::OnAnimationMontageEnd()
{
	bIsJumpingRight = bIsJumpingLeft = false;
	if (UCharacterMovementComponent* const movementComponent = GetCharacterMovement())
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		movementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}