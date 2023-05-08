// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/AnimHelpers/BaseAnimNotify_ActionEnded.h"
#include "Art/BaseRifleAnimInstance.h"

void UBaseAnimNotify_ActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	AnimInstance = Cast<UBaseRifleAnimInstance>(MeshComp->GetAnimInstance()); 
	if (AnimInstance) 
	{
		AnimInstance->OnActionEnded.Broadcast(); 
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance is null")); 
	} 
}
