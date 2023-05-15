// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameResultsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UGameResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UWidgetSwitcher* ResultsSwitch;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* Buttons;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButtonWithTextWidget* Restart;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButtonWithTextWidget* EnterMenu;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY()
		class UBaseGameInstance* GameInstance;

	//create an f timer handle
	UPROPERTY()
		FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TimeToDisplay;
	
public:

	UFUNCTION()
		void SetWin();

	UFUNCTION(BlueprintCallable)
		void OnClickRestart();

	UFUNCTION(BlueprintCallable)
		void OnClickEnterMenu();

	UFUNCTION(BlueprintCallable)
		void GoToMainMenu();
};
