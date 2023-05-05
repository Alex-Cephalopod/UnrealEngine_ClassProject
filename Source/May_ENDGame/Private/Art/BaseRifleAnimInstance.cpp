// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

UBaseRifleAnimInstance::UBaseRifleAnimInstance()
{
	DebugAttack = false;
	DebugDamaged = false;

	DeathIndex = -1;

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

	//Death animations added to list

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DeathAnimAsset1(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Death1_Ironsights.A_Death1_Ironsights'"));
	if (DeathAnimAsset1.Succeeded())
	{
		DeathAnims.Add(DeathAnimAsset1.Object);
	}
	//add another death animation to the list
	static ConstructorHelpers::FObjectFinder<UAnimSequence> DeathAnimAsset2(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Death2_Ironsights.A_Death2_Ironsights'"));
	if (DeathAnimAsset2.Succeeded())
	{
		DeathAnims.Add(DeathAnimAsset2.Object);
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
	else if (DebugDeath)
	{
		PlayDeath();
		DebugDeath = false;
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

void UBaseRifleAnimInstance::PlayDeath()
{
	//play a random death animation from the list
	DeathIndex = FMath::RandRange(0, DeathAnims.Num() - 1);
	CurrentDeathAnim = DeathAnims[DeathIndex];
}
