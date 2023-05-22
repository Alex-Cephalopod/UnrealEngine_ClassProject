// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Reload.h"
#include "AIController.h"
#include "Actors/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory); 

	AAIController* AIController = OwnerComp.GetAIOwner(); 

	APawn* Pawn = AIController->GetPawn();

	ReceiveExecuteAI(AIController, Pawn); 

	return EBTNodeResult::Succeeded;
}

void UBTTask_Reload::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	ABaseAI* AIChar = Cast<ABaseAI>(ControlledPawn);

	if (AIChar)
	{
		AIChar->Reload();
		SetFinishOnMessage(FName("ActionFinished"));
	}
}

void UBTTask_Reload::SetFinishOnMessage(FName MessageName)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
	if (OwnerComp)
	{
		OwnerComp->RegisterMessageObserver(this, MessageName);
	}
}
