// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Widgets/ButtonWithTextWidget.h"
#include "Controllers/BaseMenuPlayerController.h"
#include "Utility/BaseGameInstance.h"


void UMainMenuWidget::NativePreConstruct()
{
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));
	}
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	GameInstance->QuitGame();
}

void UMainMenuWidget::OnStartButtonClicked()
{
	GameInstance->LoadFirstLevel();
}
