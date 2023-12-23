// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NeonFableCharacter.generated.h"

UCLASS(Blueprintable)
class ANeonFableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANeonFableCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
		void HandleBasicAttackCommand();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill1Command();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill2Command();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill3Command();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill4Command();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill1LevelUp();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill2LevelUp();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill3LevelUp();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSkill4LevelUp();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleLevelUpMode();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleLevelUpModeRelease();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSummon1Command();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSummon1ReleaseCommand();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSummonSwitchLeftCommand();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleSummonSwitchRightCommand();
	UFUNCTION(BlueprintImplementableEvent)
		void HandleRotation(const FRotator& Rotation);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

};

