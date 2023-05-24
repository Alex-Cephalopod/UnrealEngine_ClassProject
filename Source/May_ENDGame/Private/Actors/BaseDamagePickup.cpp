// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDamagePickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseDamagePickup::ABaseDamagePickup()
{
	DamageValue = 2.f;

	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));

	CollisionBox->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));
}

void ABaseDamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, DamageValue, nullptr , this, DamageTypeClass);
}

void ABaseDamagePickup::PostPickup()
{
	//do nothing
}
