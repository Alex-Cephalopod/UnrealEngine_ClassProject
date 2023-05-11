// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseMenuPlayerController.h"
#include "GameModes/BaseMainMenuMode.h"
#include "Widgets/MainMenuWidget.h"

void ABaseMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//create a Main Menu Widget object and add it to the viewport
	//create a variable to hold the widget
	UMainMenuWidget* MainMenuWidget;

	//create the widget
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

	//add it to the viewport
	MainMenuWidget->AddToViewport();
}