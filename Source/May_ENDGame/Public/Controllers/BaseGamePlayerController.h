// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
};
