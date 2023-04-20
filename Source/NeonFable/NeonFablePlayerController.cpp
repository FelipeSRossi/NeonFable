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
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

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

		// Setup look input events
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &ANeonFablePlayerController::OnLookInputStarted);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnLookTriggered);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed, this, &ANeonFablePlayerController::OnLookReleased);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Canceled, this, &ANeonFablePlayerController::OnLookReleased);


		// Setup look input events
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Started, this, &ANeonFablePlayerController::OnLookMouseInputStarted);
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnLookMouseTriggered);
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Completed, this, &ANeonFablePlayerController::OnLookMouseReleased);
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Canceled, this, &ANeonFablePlayerController::OnLookMouseReleased);

		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnBasicAttackTriggered);
		EnhancedInputComponent->BindAction(SkillAction1, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSkill1Triggered);
		EnhancedInputComponent->BindAction(SkillAction2, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSkill2Triggered);
		EnhancedInputComponent->BindAction(SkillAction3, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSkill4Triggered);
		EnhancedInputComponent->BindAction(SkillAction4, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSkill4Triggered);
		EnhancedInputComponent->BindAction(SummonAction1, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSummon1Triggered);
		EnhancedInputComponent->BindAction(SummonAction1Release, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSummon1ReleaseTriggered);
		EnhancedInputComponent->BindAction(SummonSwitchLeft, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSummonSwitchLeftTriggered);
		EnhancedInputComponent->BindAction(SummonSwitchRight, ETriggerEvent::Triggered, this, &ANeonFablePlayerController::OnSummonSwitchRightTriggered);
	}
}

void ANeonFablePlayerController::OnInputStarted()
{
}

void ANeonFablePlayerController::OnLookInputStarted()
{
}

void ANeonFablePlayerController::OnLookMouseInputStarted()
{
}

void ANeonFablePlayerController::OnMoveReleased()
{
}

void ANeonFablePlayerController::OnLookReleased()
{
}

void ANeonFablePlayerController::OnLookMouseReleased()
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

void ANeonFablePlayerController::OnSkill1Triggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSkill1Command();
	}

}

void ANeonFablePlayerController::OnSkill2Triggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSkill2Command();
	}

}

void ANeonFablePlayerController::OnSkill3Triggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSkill3Command();
	}

}

void ANeonFablePlayerController::OnSkill4Triggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSkill4Command();
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

void ANeonFablePlayerController::OnSummon1ReleaseTriggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSummon1ReleaseCommand();
	}

}

void ANeonFablePlayerController::OnSummonSwitchLeftTriggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSummonSwitchLeftCommand();
	}

}

void ANeonFablePlayerController::OnSummonSwitchRightTriggered()
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->HandleSummonSwitchRightCommand();
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
		const FRotator MovementRotation(0.0f, 0.0f, 0.0f);

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

// Triggered every frame when the input is held down
void ANeonFablePlayerController::OnLookTriggered(const FInputActionValue& InputActionValue)
{
	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		FVector3d Move = FVector3d(-MoveValue.X, MoveValue.Y, 0.0);
		//ControlledPawn->SetActorRotation(Move.Rotation(), ETeleportType::None);
		ControlledCharacter->HandleRotation(Move.Rotation());
	}
}

// Triggered every frame when the input is held down
void ANeonFablePlayerController::OnLookMouseTriggered(const FInputActionValue& InputActionValue)
{

	ANeonFableCharacter* ControlledCharacter = Cast <ANeonFableCharacter>(GetCharacter());

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		FVector3d Move = FVector3d(MoveValue.X, MoveValue.Y, 0.0);
		//ControlledPawn->SetActorRotation(Move.Rotation(), ETeleportType::None);
		ControlledCharacter->HandleRotation(Move.Rotation());
	}
}





