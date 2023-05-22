// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Reload.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API UBTTask_Reload : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
	UFUNCTION(BlueprintCallable)
		void SetFinishOnMessage(FName MessageName);
	
};
