// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/BaseRifleAnimInstance.h"

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


}
