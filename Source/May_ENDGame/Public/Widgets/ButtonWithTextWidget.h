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
	//create a button called BackgroundButton with text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BackgroundButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Information;

	//create a text variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;

	//create a delegate
	UPROPERTY(BlueprintAssignable, Category = "Button")
		FButtonWidgetDelegate OnClicked;

protected:

	//call the pre construct
	virtual void NativePreConstruct() override; 

public:

	//override the OnClicked function found in BackgroundButton
	UFUNCTION()
		void OnButtonClicked();
};
