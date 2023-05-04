// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

UBaseRifleAnimInstance::UBaseRifleAnimInstance()
{
	DebugAttack = false;
	DebugDamaged = false;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AttackAnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Fire_Ironsights.A_Fire_Ironsights'"));
	if (AttackAnimAsset.Succeeded())
	{
		AttackAnim = AttackAnimAsset.Object; 
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DamagedAnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Hit_Ironsights.A_Hit_Ironsights'"));
	if (DamagedAnimAsset.Succeeded()) 
	{
		DamagedAnim = DamagedAnimAsset.Object; 
	} 
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
}

void UBaseRifleAnimInstance::PlayAttack()
{
	PlaySlotAnimationAsDynamicMontage(AttackAnim, "TestAction"); 
}

void UBaseRifleAnimInstance::PlayDamaged()
{
	PlaySlotAnimationAsDynamicMontage(DamagedAnim, "Hurt");
}