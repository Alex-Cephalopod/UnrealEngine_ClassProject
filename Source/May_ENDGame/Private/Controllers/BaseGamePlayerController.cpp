// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseGamePlayerController.h"

void ABaseGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}
