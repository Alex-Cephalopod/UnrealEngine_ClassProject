// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUDWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
//include the SlateBlueprintLibrary
#include "Blueprint/SlateBlueprintLibrary.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DynamicMaterial = CrosshairImage->GetDynamicMaterial();

	CrosshairImage->SetBrushFromMaterial(DynamicMaterial);

	SetColor(SafeColor);

}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D PixelPos;
	FVector2D ViewportPos;

	FGeometry CachedGeometry = CrosshairImage->GetCachedGeometry();

	//get absolute size of cached geometry
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

	FHitResult HitResult;

	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), WorldPos, WorldPos + (WorldDir * 100000), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (bHit)
	{
		//cast hitResult.hitactor to a pawn
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
