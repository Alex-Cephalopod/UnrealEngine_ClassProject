// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/BaseDamageTypeFire.h"
#include "Components/BaseEffectsComponent.h"

UBaseDamageTypeFire::UBaseDamageTypeFire()
{
	EffectClass = UBaseEffectsComponent::StaticClass();
}

void UBaseDamageTypeFire::StartEffect(AActor* DamagedActor, AActor* DamageCauser) const
{
	UActorComponent* ActorsComponent = DamagedActor->GetComponentByClass(EffectClass);

	if (ActorsComponent)
	{
		UBaseEffectsComponent* BaseEffectsComponent = Cast<UBaseEffectsComponent>(ActorsComponent);
		if (BaseEffectsComponent)
			BaseEffectsComponent->StartEffects(EEffects::EE_Burning, DamageCauser);
	}
}
