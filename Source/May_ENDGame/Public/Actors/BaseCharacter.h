// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IBasePickup.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseCharacter : public ACharacter, public IIBasePickup
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UChildActorComponent* WeaponChild;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBaseHealthComponent* HealthComponent;

	UPROPERTY()
		class ABaseWeapon* Weapon;

	UPROPERTY()
		class UBaseRifleAnimInstance* AnimInstance; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseLauncher> LauncherClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseWeapon> RifleClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region CustomEvents
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Attacks();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SpecialAttack();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void Damaged();

	UFUNCTION(BlueprintCallable, Category = "Anim")
		void PlayAttack(); 

	UFUNCTION(BlueprintCallable, Category = "Anim")
		void PlayDeath();

	UFUNCTION(BlueprintCallable, Category = "Anim")
		void AnimEnded();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void OwnerDied();

	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual void HandleDeath();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		void SwapWeapons();

	UFUNCTION(BlueprintCallable, Category = "References")
		virtual void SetReferences();

	UFUNCTION(BlueprintCallable, Category = "References")
		void BindWeapAndAnimEvents();

	bool CanPickupHealth() const override;
	bool ShouldPickupHealth() const override;

#pragma endregion
};
