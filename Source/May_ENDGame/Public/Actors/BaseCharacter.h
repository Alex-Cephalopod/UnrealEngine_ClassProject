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

	//create a BaseHealthComponent variable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBaseHealthComponent* HealthComponent;

	//create a base weapon variable
	UPROPERTY()
		class ABaseWeapon* Weapon;

	//Create a variable for the BaseRigleAnimInstance
	UPROPERTY()
		class UBaseRifleAnimInstance* AnimInstance; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<class ABaseWeapon> WeaponClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//create a function to attack called Attacks
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Attacks();

};
