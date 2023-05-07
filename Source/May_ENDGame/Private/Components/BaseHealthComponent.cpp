// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseHealthComponent.h"

// Sets default values for this component's properties
UBaseHealthComponent::UBaseHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	CurrentHealth -= Damage;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if (CurrentHealth > 0)
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

