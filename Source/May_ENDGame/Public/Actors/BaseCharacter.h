// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//include the header file for the BaseRifleAnimInstance
//#include "Art/BaseRifleAnimInstance.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Create a TSubClassOf of the BaseRifleAnimInstance
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UBaseRifleAnimInstance> RifleAnimClass;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
