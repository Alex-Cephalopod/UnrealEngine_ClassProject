// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/BaseAI.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner(); 

	APawn* Pawn = AIController->GetPawn(); 

	ReceiveExecuteAI(AIController, Pawn);

	return EBTNodeResult::Succeeded;

}

void UBTTask_Shoot::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	ABaseAI* AICharacter = Cast<ABaseAI>(ControlledPawn);

	if (AICharacter)
	{
		AICharacter->Shoot();
		SetFinishOnMessage(FName("ActionFinished"));
	}
}

void UBTTask_Shoot::SetFinishOnMessage(FName MessageName)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
	if (OwnerComp)
	{
		OwnerComp->RegisterMessageObserver(this, MessageName);
	}
}