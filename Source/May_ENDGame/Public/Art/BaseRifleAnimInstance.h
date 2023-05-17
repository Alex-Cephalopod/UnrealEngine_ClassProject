// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseRifleAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FRifleDelegate);
/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBaseRifleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseRifleAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayAttack();

	UFUNCTION(BlueprintNativeEvent, Category = "Function")
		void PlayDamaged();

	virtual void PlayDamaged_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayDamageWithFloat(float _Percent);

	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayDeath();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void DeathEnded();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayReload();

	UPROPERTY(BlueprintAssignable, Category = "Function")
		FRifleDelegate OnActionEnded;

	UPROPERTY(BlueprintAssignable, Category = "Function")
		FRifleDelegate OnReloadWeapon;

	UPROPERTY(BlueprintAssignable, Category = "Function")
		FRifleDelegate OnDeathEnded;
	
protected:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int DeathIndex;

	UPROPERTY()
		FTimerHandle DeathTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimSequence* DamagedAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* CurrentDeathAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* ReloadAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UAnimSequence*> DeathAnims;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugDeath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugReload;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName ActionSlot = "Action";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName HurtSlot = "Hurt";

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
		void PersonaUpdate();

	virtual void PersonaUpdate_Implementation(); 
};
