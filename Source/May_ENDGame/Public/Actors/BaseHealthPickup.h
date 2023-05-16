// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "BaseHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseHealthPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ABaseHealthPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
		float HealthValue;

	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* InvalidSound;

protected:

public:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	bool CanPickUp(AActor* OtherActor) const override;

	bool ShouldPickUp(AActor* OtherActor) const override;

	void HandleNoPickup() override;
};
