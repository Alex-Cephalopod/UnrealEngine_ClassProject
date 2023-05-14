// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
		bool bValidHit;

	UPROPERTY()
		FVector EndPoint;

	UPROPERTY()
		FVector HitLocation;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* CrosshairImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor DangerColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor SafeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ColorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldDir;

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetColor(FLinearColor Color);

	void SetDangerColor();

	void SetSafeColor();

	UFUNCTION(BlueprintCallable)
		bool GetEnd(FVector& _Hit, FVector& _EndPoint) const;

	UFUNCTION(BlueprintCallable)
		void SetHealth(float _Percent);
};
