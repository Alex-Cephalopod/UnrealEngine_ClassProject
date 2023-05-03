// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseRifleAnimInstance.generated.h"

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

	//create a function called PlayDamaged
	UFUNCTION(BlueprintCallable, Category = "Function")
		void PlayDamaged();
	
protected:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	//create a speed variable that can be accessed in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	//create a direction variable that can be accessed in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Direction;

	//create a variable of Anim Sequence called AttackAnim
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* AttackAnim;

	//create a variable of Anim Sequence called DamagedAnim
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimSequence* DamagedAnim;

	//create a bool variable called DebugAttack
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugAttack;

	//create a bool variable called DebugDamaged
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool DebugDamaged;

	//Create a blueprint native event called PersonaUpdate
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
		void PersonaUpdate();

	virtual void PersonaUpdate_Implementation(); 
};
