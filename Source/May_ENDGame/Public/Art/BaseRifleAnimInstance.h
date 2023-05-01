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
	
protected:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	//create a speed variable that can be accessed in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	//create a direction variable that can be accessed in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Direction;
};
