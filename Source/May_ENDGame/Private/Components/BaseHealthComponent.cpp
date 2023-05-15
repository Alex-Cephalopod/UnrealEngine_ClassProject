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
			OnDamageHealth.Broadcast(CurrentHealth/MaxHealth);
			UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
		}
		else
		{
			OnHealed.Broadcast(CurrentHealth / MaxHealth);
		}
	}
	else {
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UBaseHealthComponent::DamageHappened);
		OnDeathHealth.Broadcast(0);
		UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	}
}

bool UBaseHealthComponent::IsFullHealth() const
{
	return (CurrentHealth/MaxHealth) > 0.99f;
}