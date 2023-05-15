// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameResultsWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Utility/BaseGameInstance.h"
#include "Components/VerticalBox.h"
#include "Widgets/ButtonWithTextWidget.h"

void UGameResultsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

	Restart->OnClicked.AddDynamic(this, &UGameResultsWidget::OnClickRestart);
	EnterMenu->OnClicked.AddDynamic(this, &UGameResultsWidget::OnClickEnterMenu);

}

void UGameResultsWidget::SetWin()
{
	Buttons->SetVisibility(ESlateVisibility::Hidden);

	ResultsSwitch->SetActiveWidgetIndex(1);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGameResultsWidget::GoToMainMenu, TimeToDisplay, false);
}

void UGameResultsWidget::OnClickRestart()
{
	GameInstance->LoadCurrentLevel();
}

void UGameResultsWidget::OnClickEnterMenu()
{
	GameInstance->LoadMainMenu();
}

void UGameResultsWidget::GoToMainMenu()
{
	GameInstance->LoadMainMenu();
}
