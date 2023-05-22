// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BaseFindPointTask.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBaseFindPointTask : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		float SearchRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		FBlackboardKeySelector BlackboardKeyPoint;
	
};
