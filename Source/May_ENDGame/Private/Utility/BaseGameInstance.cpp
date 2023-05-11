// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UBaseGameInstance::LoadLevel()
{
	UGameplayStatics::OpenLevel(this, LevelNames[FirstLevel]);
}

void UBaseGameInstance::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
