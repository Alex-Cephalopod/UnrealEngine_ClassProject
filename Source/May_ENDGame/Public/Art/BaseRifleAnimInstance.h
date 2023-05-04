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

	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayDamaged();

	UPROPERTY(BlueprintAssignable, Category = "Function")
		FRifleDelegate OnActionEnded;
	
protected:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* DamagedAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugDamaged;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
		void PersonaUpdate();

	virtual void PersonaUpdate_Implementation(); 
};
