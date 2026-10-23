// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Portfolio.h"
#include "InteractInterface.h"
#include "PickupInterface.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "Engine/Hitresult.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

APortfolioCharacter::APortfolioCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOwnerNoSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	PhysicsComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicasHandle"));
}

void APortfolioCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * HitRange;

	Hit = GetWorld()->LineTraceSingleByChannel(
		Result,
		Start,
		End,
		ECC_Visibility
	);

	switch (CurrentState)
	{
	case EPlayerState::None:
		break;
	case EPlayerState::Pickup:
		PhysicsComponent->SetTargetLocationAndRotation(
			End,
			GetActorRotation()
		);
		break;
	default:
		break;
	}
}

void APortfolioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APortfolioCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APortfolioCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APortfolioCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APortfolioCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APortfolioCharacter::LookInput);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APortfolioCharacter::DoInteract);
	}
	else
	{
		UE_LOG(LogPortfolio, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void APortfolioCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void APortfolioCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void APortfolioCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APortfolioCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void APortfolioCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void APortfolioCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void APortfolioCharacter::DoInteract()
{
	AActor* HitActor = Result.GetActor();
	switch (CurrentState) {
	default:
		break;
	case EPlayerState::None:
		if (IInteractInterface* Interact = Cast<IInteractInterface>(HitActor)) {
			if (!Interact->CanInteract()) {
				return;
			}
			if (IPickupInterface* Pickup = Cast<IPickupInterface>(HitActor)) {
				PhysicsComponent->GrabComponentAtLocationWithRotation(
					Result.GetComponent(),
					NAME_None,
					Result.ImpactPoint,
					Result.GetActor()->GetActorRotation()
				);
				Pickup->OnPickup(this);
				CurrentState = EPlayerState::Pickup;
			}
		}
		break;
	case EPlayerState::Pickup:
		PhysicsComponent->ReleaseComponent();
		CurrentState = EPlayerState::None;
		break;

	}

}