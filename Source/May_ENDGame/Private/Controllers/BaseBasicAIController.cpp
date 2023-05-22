// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseBasicAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionTypes.h"


ABaseBasicAIController::ABaseBasicAIController()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

//void ABaseBasicAIController::BeginPlay()
//{
//	if (AIPerceptionComponent)
//	{
//		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseBasicAIController::OnTargetPerceptionUpdate);
//	}
//}

void ABaseBasicAIController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	RunBehaviorTree(BTAsset);

	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseBasicAIController::OnTargetPerceptionUpdate);
	}
}

void ABaseBasicAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(PlayerKey, Actor);
	}
	else
	{
		Blackboard->ClearValue(PlayerKey);
	}
}