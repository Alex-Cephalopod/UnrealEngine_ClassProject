// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseHealthPickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseHealthPickup::ABaseHealthPickup()
{
	//PrimaryActorTick.bStartWithTickEnabled = false;
	HealthValue = -1.5;
	
	CollisionBox->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.f));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));
	ParticleSystem->SetupAttachment(CollisionBox);
}

void ABaseHealthPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, HealthValue, nullptr, this, nullptr);
}

bool ABaseHealthPickup::CanPickUp(AActor* OtherActor, bool yes) const
{
	//OtherActor->CanPick
	return yes = false;
}
