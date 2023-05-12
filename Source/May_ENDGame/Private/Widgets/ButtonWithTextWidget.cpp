// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ButtonWithTextWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonWithTextWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Information->SetText(Text);

	BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithTextWidget::OnButtonClicked);
}

void UButtonWithTextWidget::OnButtonClicked()
{
	OnClicked.Broadcast();
}


