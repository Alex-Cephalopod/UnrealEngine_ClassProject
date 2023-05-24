// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseEffectsComponent.generated.h"

UENUM(BlueprintType)
enum class EEffects : uint8
{
	EE_Burning UMETA(DisplayName = "Burning"),
	EE_NumEffects UMETA(DisplayName = "NumEffects")

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAY_ENDGAME_API UBaseEffectsComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseEffectsComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseFireEffect> FireEffectClass;

public:	

	UFUNCTION()
		void StartEffects(EEffects EffectType, AActor* DamageCauser);
};
