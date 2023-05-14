// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Art/BaseRifleAnimInstance.h"

ABaseAI::ABaseAI()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Attacks();
}

void ABaseAI::BindWeapAndAnimEvents()
{
	Super::BindWeapAndAnimEvents();

	if (!AnimInstance->OnDeathEnded.IsBound())
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABaseAI::K2_DestroyActor);
}

void ABaseAI::WhenPlayerDies()
{
	SetActorTickEnabled(false);
}
