// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFireEffect.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseFireEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFireEffect();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireParticle")
		UParticleSystemComponent* FireEffect;

	UPROPERTY(EditAnywhere)
		float FireDamage;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
