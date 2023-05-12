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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageValue;

protected:

public:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	virtual void PostPickup() override;

};
