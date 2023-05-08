// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABasePlayer : public ABaseCharacter, public IIBasePickup
{
	GENERATED_BODY()
	
public:

	ABasePlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PlayerShoot();
	void Jump();
	
	void HandleDeath() override;

	//get a begin play function to get the player controller
	virtual void BeginPlay() override;

	//implement the interface function
	bool CanPickupHealth(bool yes = false) const override;


protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class APlayerController* PlayerController;
};
