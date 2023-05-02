// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//create a child actor component for the weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UChildActorComponent* WeaponChild;

	//create a BaseWeapon class variable
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseWeapon> WeaponClass;*/
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<class ABaseWeapon> WeaponClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
