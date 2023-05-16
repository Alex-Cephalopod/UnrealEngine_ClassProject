// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseFireEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseFireEffect::ABaseFireEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//FireDamage = 10.0f;
	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEffect"));
	SetRootComponent(FireEffect);

}

// Called when the game starts or when spawned
//void ABaseFireEffect::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
void ABaseFireEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DPS = FireDamage * DeltaTime;

	//call the apply damage function
	UGameplayStatics::ApplyDamage(GetAttachParentActor(), DPS, nullptr, GetOwner(), nullptr);

}

