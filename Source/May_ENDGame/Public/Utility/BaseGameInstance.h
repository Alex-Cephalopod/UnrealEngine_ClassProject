// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//make an array of FName to store the names of the levels
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		TArray<FName> LevelNames;

	//create an int to store level index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		int FirstLevel;

protected:

public:

	UFUNCTION(BlueprintCallable)
		void LoadLevel();

	UFUNCTION(BlueprintCallable)
		void QuitGame();
};
