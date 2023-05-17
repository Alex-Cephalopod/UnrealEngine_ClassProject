// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/AnimHelpers/BaseAnimNotify_ReloadWeapon.h"
#include "Art/BaseRifleAnimInstance.h"

void UBaseAnimNotify_ReloadWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	AnimInstance = Cast<UBaseRifleAnimInstance>(MeshComp->GetAnimInstance());

	if (AnimInstance)
	{
		AnimInstance->OnReloadWeapon.Broadcast();
	}
}
