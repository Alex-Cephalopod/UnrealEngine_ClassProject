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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		//make a TSubclassOf AActors
		TSubclassOf<class AActor> AIClass;
	
public:

	UFUNCTION()
		void RemoveEnemy(AActor* DestroyedActor);
};
