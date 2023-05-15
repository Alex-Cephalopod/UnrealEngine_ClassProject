// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseHealthPickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"

ABaseHealthPickup::ABaseHealthPickup()
{
	HealthValue = -1.5;
	
	CollisionBox->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.f));

	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));
}

void ABaseHealthPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, HealthValue, nullptr, this, nullptr);
}

bool ABaseHealthPickup::CanPickUp(AActor* OtherActor) const
{
	if (Cast<ABasePlayer>(OtherActor))
	{
		return Cast<ABasePlayer>(OtherActor)->CanPickupHealth();
	}
	else
	{
		return false;
	}
}

bool ABaseHealthPickup::ShouldPickUp(AActor* OtherActor) const
{ 
	if (Cast<ABasePlayer>(OtherActor)) 
	{
		return Cast<ABasePlayer>(OtherActor)->ShouldPickupHealth(); 
	}
	else
	{
		return false;
	}
}
