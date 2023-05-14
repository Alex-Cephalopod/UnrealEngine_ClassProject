// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseMenuPlayerController.h"
#include "GameModes/BaseMainMenuMode.h"
#include "Widgets/MainMenuWidget.h"

void ABaseMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UMainMenuWidget* MainMenuWidget;
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetWidgetToFocus(MainMenuWidget->TakeWidget());
	SetInputMode(InputModeData);


}