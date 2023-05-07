// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDamagePickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseDamagePickup::ABaseDamagePickup()
{
	DamageValue = 2.f;
	//start with tick enabled = false
	//PrimaryActorTick.bStartWithTickEnabled = false;

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	ParticleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));

	CollisionBox->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));

	ParticleSystem->SetupAttachment(CollisionBox);
}

void ABaseDamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	//call ApplyDamage, where other actor is OtherActor, the damage value is DamageValue, and the DamageCauser is this
	UGameplayStatics::ApplyDamage(OtherActor, DamageValue, nullptr , this, nullptr);
}

void ABaseDamagePickup::PostPickup()
{

}
