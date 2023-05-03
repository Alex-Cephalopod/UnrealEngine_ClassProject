// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseAI : public ABaseCharacter
{
	GENERATED_BODY()

public:
	//create constructor
	ABaseAI();
	
protected:

public:
	//create a function called Tick
	virtual void Tick(float DeltaTime) override;
};
