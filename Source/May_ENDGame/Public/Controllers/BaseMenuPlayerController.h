// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

protected:
	virtual void BeginPlay() override;
	
};
