// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/IBaseDamageType.h"
#include "BaseDamageTypeFire.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBaseDamageTypeFire : public UDamageType, public IIBaseDamageType
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		TSubclassOf<class UBaseEffectsComponent> EffectClass;

public:
	UBaseDamageTypeFire();
	void StartEffect(AActor* DamagedActor, AActor* DamageCauser) const override;
	
};
