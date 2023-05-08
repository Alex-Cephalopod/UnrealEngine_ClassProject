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

	//add a particle system to the pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
		UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
		float HealthValue;

protected:

public:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	virtual bool CanPickUp(AActor* OtherActor, bool yes) const override;

};
