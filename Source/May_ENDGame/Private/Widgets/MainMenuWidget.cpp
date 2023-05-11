// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Widgets/ButtonWithTextWidget.h"
#include "Controllers/BaseMenuPlayerController.h"
#include "Utility/BaseGameInstance.h"


void UMainMenuWidget::NativePreConstruct()
{
	//cast game instance to base game instance
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

//create a function to call the delegate when the quit button is clicked
void UMainMenuWidget::OnQuitButtonClicked()
{
	GameInstance->QuitGame();
}

void UMainMenuWidget::OnStartButtonClicked()
{
	GameInstance->LoadLevel();
}
