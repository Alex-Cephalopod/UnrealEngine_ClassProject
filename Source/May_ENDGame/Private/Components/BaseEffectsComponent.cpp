// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseEffectsComponent.h"
#include "Actors/BaseFireEffect.h"

// Sets default values for this component's properties
UBaseEffectsComponent::UBaseEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
//void UBaseEffectsComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}


// Called every frame
void UBaseEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseEffectsComponent::StartEffects(EEffects EffectType, AActor* DamageCauser)
{
	switch (EffectType)
	{
	case EEffects::EE_Burning:
	{
		//spawn actor
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Owner = DamageCauser;
		ABaseFireEffect* FireEffect = GetWorld()->SpawnActor<ABaseFireEffect>(FireEffectClass, GetComponentTransform(), SpawnParams);

		//attach actor to actor
		FireEffect->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		break;
	}
	case EEffects::EE_NumEffects:
	{
		UE_LOG(LogTemp, Error, TEXT("Bad Effect Type"));
		break;
	}
	}
}

