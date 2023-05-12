// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWithTextWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonWidgetDelegate);
/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UButtonWithTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BackgroundButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Information;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;

	UPROPERTY(BlueprintAssignable, Category = "Button")
		FButtonWidgetDelegate OnClicked;

protected:

	virtual void NativePreConstruct() override; 

public:

	UFUNCTION()
		void OnButtonClicked();
};
