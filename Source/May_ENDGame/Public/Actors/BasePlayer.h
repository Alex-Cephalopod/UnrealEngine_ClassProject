// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	ABasePlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void HandleDeath(float _Percent) override;

	virtual void BeginPlay() override;

	bool CanPickupHealth() const override;

	bool ShouldPickupHealth() const override; 

	void SetReferences() override;

	virtual FRotator GetBaseAimRotation() const override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UHUDWidget> HUDWidgetClass;

	UPROPERTY()
		class UHUDWidget* HUDWidget;

};
