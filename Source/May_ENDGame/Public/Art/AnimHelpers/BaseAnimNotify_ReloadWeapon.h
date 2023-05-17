// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "BaseAnimNotify_ReloadWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBaseAnimNotify_ReloadWeapon : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UBaseRifleAnimInstance* AnimInstance;
	
};
