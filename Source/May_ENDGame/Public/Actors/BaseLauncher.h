// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseWeapon.h"
#include "BaseLauncher.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseLauncher : public ABaseWeapon
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
