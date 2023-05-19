// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBaseDamageType.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UIBaseDamageType : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAY_ENDGAME_API IIBaseDamageType
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		virtual void StartEffect(AActor* DamagedActor, AActor* DamageCauser) const = 0;
};
