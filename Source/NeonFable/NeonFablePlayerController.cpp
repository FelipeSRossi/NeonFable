// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeonFablePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NeonFableCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ANeonFablePlayerController::ANeonFablePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ANeonFablePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ANeonFablePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{

		// Setup movement input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ANeonFablePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnMoveTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ANeonFablePlayerController::OnMoveReleased);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ANeonFablePlayerController::OnMoveReleased);

		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnBasicAttackTriggered);
		EnhancedInputComponent->BindAction(SummonAction1, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSummon1Triggered);
	}
}

void ANeonFablePlayerController::OnInputStarted()
{
}


void ANeonFablePlayerController::OnMoveReleased()
{
}

void ANeonFablePlayerController::OnBasicAttackTriggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleBasicAttackCommand();
	}

}

void ANeonFablePlayerController::OnSummon1Triggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSummon1Command();
	}

}


// Triggered every frame when the input is held down
void ANeonFablePlayerController::OnMoveTriggered(const FInputActionValue& InputActionValue)
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, ControlledPawn->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			ControlledPawn->AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			ControlledPawn->AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}




