// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

UBaseRifleAnimInstance::UBaseRifleAnimInstance()
{
	DebugAttack = false;
	//safely give AttackAnim a value
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AttackAnimAsset(TEXT("AnimSequence'/Game/END_Starter/Mannequin/A_Fire_Ironsights.A_Fire_Ironsights'"));
	if (AttackAnimAsset.Succeeded())
	{
		AttackAnim = AttackAnimAsset.Object; 
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
}

void UBaseRifleAnimInstance::PlayAttack()
{
	//call PlaySlotAnimationAsDynamicMontage function
	PlaySlotAnimationAsDynamicMontage(AttackAnim, "Action"); 
}
