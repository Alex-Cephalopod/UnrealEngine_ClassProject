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
	// Sets default values for this character's properties
	ABasePlayer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//create a spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComp;

	//create a camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComp;
};
