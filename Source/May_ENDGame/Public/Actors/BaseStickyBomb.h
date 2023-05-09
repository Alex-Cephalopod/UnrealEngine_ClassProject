// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBullet.h"
#include "BaseStickyBomb.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseStickyBomb : public ABaseBullet
{
	GENERATED_BODY()

public:
	//constructor
	ABaseStickyBomb();

	UPROPERTY()
		float DamageRadius;

protected:

public:

	void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& SweepResult) override;

	void SpecialAttack() override;
	
};
