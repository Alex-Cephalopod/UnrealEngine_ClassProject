// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Art/BaseRifleAnimInstance.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/BaseWeapon.h"


ABaseAI::ABaseAI()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ABaseAI::BeginPlay()
{

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		Blackboard = AIController->GetBlackboardComponent();
	}

	Super::BeginPlay();
}

void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Attacks();
}

void ABaseAI::BindWeapAndAnimEvents()
{
	Super::BindWeapAndAnimEvents();

	if (!AnimInstance->OnDeathEnded.IsBound())
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABaseAI::K2_DestroyActor);

	AnimInstance->OnActionEnded.AddDynamic(this, &ABaseAI::ActionEnded);

	Weapon->OnAmmoUpdate.AddDynamic(this, &ABaseAI::UpdateBlackboard);
}

void ABaseAI::WhenPlayerDies()
{
	SetActorTickEnabled(false);
}

void ABaseAI::ActionEnded()
{
	UAIBlueprintHelperLibrary::SendAIMessage(this, FName("ActionFinished"), nullptr);
}

void ABaseAI::UpdateBlackboard(float _Current, float _Max)
{
	Blackboard->SetValueAsFloat(AmmoKey, _Current);
}

void ABaseAI::Shoot()
{
	Attacks();
}

void ABaseAI::AIReload()
{
	Weapon->RequestReload();
}
