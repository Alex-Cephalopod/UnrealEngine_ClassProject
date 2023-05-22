// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseFindPointTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBaseFindPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();

    APawn *Pawn = AIController->GetPawn();

    ReceiveExecuteAI(AIController, Pawn);

    return EBTNodeResult::Succeeded;
}

void UBaseFindPointTask::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    FVector Point;
    NavSystem->K2_GetRandomReachablePointInRadius(GetWorld(), ControlledPawn->GetActorLocation(), Point, SearchRadius); 

    OwnerController->GetBlackboardComponent()->SetValueAsVector(BlackboardKeyPoint.SelectedKeyName, Point); 
}
