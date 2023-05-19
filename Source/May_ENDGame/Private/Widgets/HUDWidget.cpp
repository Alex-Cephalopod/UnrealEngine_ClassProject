// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUDWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DynamicMaterial = CrosshairImage->GetDynamicMaterial();

	CrosshairImage->SetBrushFromMaterial(DynamicMaterial);

	SetColor(SafeColor);

	DynamicMaterials.Add(DynamicMaterial);
	DynamicMaterials.Add(CrosshairImage_Launcher->GetDynamicMaterial());

	CrosshairImage_Launcher->SetBrushFromMaterial(CrosshairImage_Launcher->GetDynamicMaterial());

}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D PixelPos;
	FVector2D ViewportPos;

	FGeometry CachedGeometry = CrosshairImage->GetCachedGeometry();

	FVector2D AbsoluteSize = CachedGeometry.GetAbsoluteSize();
	AbsoluteSize *= 0.5f;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), CachedGeometry, FVector2D(0, 0), PixelPos, ViewportPos);

	PixelPos += AbsoluteSize;

	GetOwningPlayer()->DeprojectScreenPositionToWorld(PixelPos.X, PixelPos.Y, WorldPos, WorldDir);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwningPlayerPawn());

	EndPoint = WorldPos + (WorldDir * 100000);

	FHitResult HitResult;

	bValidHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), WorldPos, EndPoint, ObjectTypes,
		false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (bValidHit)
	{
		HitLocation = HitResult.Location;
		APawn* Pawn = Cast<APawn>(HitResult.Actor);
		if (Pawn)
		{
			SetColor(DangerColor);
		}
		else
		{
			SetColor(SafeColor);
		}
	}
	else 
	{
		SetColor(SafeColor);
	}
}

void UHUDWidget::SetColor(FLinearColor Color)
{
	DynamicMaterial->SetVectorParameterValue(ColorKey, Color);
}

void UHUDWidget::SetDangerColor()
{
	DynamicMaterial->SetVectorParameterValue(ColorKey, DangerColor);
}

void UHUDWidget::SetSafeColor()
{
	DynamicMaterial->SetVectorParameterValue(ColorKey, SafeColor);
}

bool UHUDWidget::GetEnd(FVector& _Hit, FVector& _EndPoint) const
{
	_Hit = HitLocation;
	_EndPoint = EndPoint;
	return bValidHit;
}

void UHUDWidget::SetHealth(float _Percent)
{
	HealthBar->SetPercent(_Percent);
}

void UHUDWidget::SetAmmo(float _Current, float _Max)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(_Current))); 
	MaxAmmoText->SetText(FText::FromString(FString::FromInt(_Max))); 
}

void UHUDWidget::SetWeaponIndex(int32 _Index)
{
	CrosshairSwitcher->SetActiveWidgetIndex(_Index);

	IconSwitcher->SetActiveWidgetIndex(_Index);

	if (_Index >= 0 && _Index < DynamicMaterials.Num())
	{
		DynamicMaterial = DynamicMaterials[_Index];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid index"));
	}
}
