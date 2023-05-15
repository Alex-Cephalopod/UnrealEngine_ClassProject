// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic"); 
	CollisionBox->SetGenerateOverlapEvents(true); 
	SetRootComponent(CollisionBox);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(CollisionBox);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
}

bool ABasePickup::CanPickUp(AActor* OtherActor) const
{
	return true;
}

bool ABasePickup::ShouldPickUp(AActor* OtherActor) const
{
	return true;
}

void ABasePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickUp(OtherActor))
	{
		if (ShouldPickUp(OtherActor))
		{
			HandlePickup(OtherActor, SweepResult);
			PostPickup();
		}
	}
}

void ABasePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{

}

void ABasePickup::PostPickup()
{
	Destroy();
}

