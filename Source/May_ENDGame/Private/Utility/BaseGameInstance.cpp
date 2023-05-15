// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"



void UBaseGameInstance::LoadFirstLevel()
{
	LoadLevelSafe(FirstLevel);
}

void UBaseGameInstance::LoadMainMenu()
{
	LoadLevelSafe(MainMenu);
}

void UBaseGameInstance::LoadCurrentLevel()
{
	LoadLevelSafe(CurrentLevel);
}

void UBaseGameInstance::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UBaseGameInstance::LoadLevelSafe(int MapIndex)
{
	if (MapIndex >= 0 && MapIndex < LevelNames.Num())
	{
		CurrentLevel = MapIndex;
		UGameplayStatics::OpenLevel(this, LevelNames[CurrentLevel]);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Index %d out of range"), CurrentLevel);
	}

}