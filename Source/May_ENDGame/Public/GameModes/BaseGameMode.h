// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	UPROPERTY()
		int32 CurrentEnemyCount;

	UPROPERTY()
		APlayerController* ActivePlayerController;

	UPROPERTY()
		class ABasePlayer* ActivePlayer;

	UPROPERTY()
		class UGameResultsWidget* ResultsWidget;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> AIClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UGameResultsWidget> GameResultsWidgetClass;
	
public:

	UFUNCTION()
		void RemoveEnemy(AActor* DestroyedActor);

	UFUNCTION()
		void RemovePlayer(AActor* DestroyedActor);
};
