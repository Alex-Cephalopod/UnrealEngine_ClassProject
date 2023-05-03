// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseHealthComponent.h"

// Sets default values for this component's properties
UBaseHealthComponent::UBaseHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//set start with tick enabled to false
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

	//clamp current health to 0 and MaxHealth
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if (CurrentHealth > 0)
	{
		//Call OnDamaged delegate
		OnDamaged.Broadcast();

		//print current health to screen
		UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	}
	else {
		//unbind from owner's OnTakeAnyDamage event
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UBaseHealthComponent::DamageHappened);
		UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	}
}

