// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

UBaseRifleAnimInstance::UBaseRifleAnimInstance()
{
	DebugAttack = false;
	DebugDamaged = false;
	//safely give AttackAnim a value
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AttackAnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Fire_Ironsights.A_Fire_Ironsights'"));
	if (AttackAnimAsset.Succeeded())
	{
		AttackAnim = AttackAnimAsset.Object; 
	}

	//safely give DamagedAnim a value of AnimSequence'/Game/END_Starter/Mannequin/A_Hit_Ironsights.A_Hit_Ironsights'
	static ConstructorHelpers::FObjectFinder<UAnimSequence> DamagedAnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Hit_Ironsights.A_Hit_Ironsights'"));
	if (DamagedAnimAsset.Succeeded()) 
	{
		DamagedAnim = DamagedAnimAsset.Object; 
	} 
}

void UBaseRifleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//get the pawn
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		//get the speed of the pawn
		Speed = Pawn->GetVelocity().Size(); 
		//get the direction of the pawn
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
	//call PlaySlotAnimationAsDynamicMontage function
	PlaySlotAnimationAsDynamicMontage(AttackAnim, "Action"); 
}

void UBaseRifleAnimInstance::PlayDamaged()
{
	// call PlaySlotAnimationAsDynamicMontage function
	PlaySlotAnimationAsDynamicMontage(DamagedAnim, "Action");
}