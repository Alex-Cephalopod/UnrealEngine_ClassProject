// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "BaseDamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseDamagePickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ABaseDamagePickup();

	//create a particle system component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		class UParticleSystemComponent* ParticleSystem;

	//create a damage value as a float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageValue;

protected:

public:

	//grab the override function of HandlePickup from the base class
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	virtual void PostPickup() override;

};
