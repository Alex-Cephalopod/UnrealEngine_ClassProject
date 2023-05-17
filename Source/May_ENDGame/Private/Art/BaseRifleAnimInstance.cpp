// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

UBaseRifleAnimInstance::UBaseRifleAnimInstance()
{
	DebugAttack = false;
	DebugDamaged = false;
	DebugDeath = false;
	DebugReload = false;
	DeathIndex = -1;
}

void UBaseRifleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		Speed = Pawn->GetVelocity().Size();
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
	else
	{
		PersonaUpdate();
	}
}

void UBaseRifleAnimInstance::PersonaUpdate_Implementation()
{
	if (DebugAttack)
	{
		PlayAttack();
		DebugAttack = false;
	}
	else if (DebugDamaged)
	{
		PlayDamaged();
		DebugDamaged = false;
	}
	else if (DebugDeath)
	{
		PlayDeath();
		DebugDeath = false;
	}
	else if (DebugReload)
	{
		PlayReload();
		DebugReload = false;
	}
}

void UBaseRifleAnimInstance::PlayAttack()
{
	PlaySlotAnimationAsDynamicMontage(AttackAnim, ActionSlot); 
}

void UBaseRifleAnimInstance::PlayDamaged_Implementation()
{

	//call the IsPlayingSlotAnimation function to check if the animation is playing
	if (IsPlayingSlotAnimation(DamagedAnim, HurtSlot))
	{
		
	}
	else
	{
		PlaySlotAnimationAsDynamicMontage(DamagedAnim, HurtSlot);
	}
}

void UBaseRifleAnimInstance::PlayDamageWithFloat(float _Percent)
{
	PlayDamaged();
}

void UBaseRifleAnimInstance::PlayDeath()
{
	DeathIndex = FMath::RandRange(0, DeathAnims.Num() - 1);
	CurrentDeathAnim = DeathAnims[DeathIndex];
	CurrentDeathAnim->GetPlayLength();
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &UBaseRifleAnimInstance::DeathEnded, CurrentDeathAnim->GetPlayLength(), false);
}

void UBaseRifleAnimInstance::DeathEnded()
{
	OnDeathEnded.Broadcast();
}

void UBaseRifleAnimInstance::PlayReload()
{
	PlaySlotAnimationAsDynamicMontage(ReloadAnim, ActionSlot);
}
