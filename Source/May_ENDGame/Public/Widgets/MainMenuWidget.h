// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButtonWithTextWidget* StartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButtonWithTextWidget* QuitButton;

	UPROPERTY(BlueprintReadOnly)
		class UBaseGameInstance* GameInstance;

	UFUNCTION(BlueprintCallable)
		void OnQuitButtonClicked();

	UFUNCTION(BlueprintCallable)
		void OnStartButtonClicked();

	
};
