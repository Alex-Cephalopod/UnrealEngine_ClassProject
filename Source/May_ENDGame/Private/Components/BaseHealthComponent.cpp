// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseHealthComponent.h"

// Sets default values for this component's properties
UBaseHealthComponent::UBaseHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	MaxHealth = 5.f;
}


// Called when the game starts
void UBaseHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	InitHealth();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UBaseHealthComponent::DamageHappened);

}

void UBaseHealthComponent::InitHealth()
{
	CurrentHealth = MaxHealth;
}

void UBaseHealthComponent::DamageHappened(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if (FMath::Clamp(CurrentHealth -= Damage, 0.f, MaxHealth) > 0) 
	{
		if (Damage > 0)
		{
			OnDamaged.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
		}
	}
	else {
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UBaseHealthComponent::DamageHappened);
		OnDeath.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	}
}

