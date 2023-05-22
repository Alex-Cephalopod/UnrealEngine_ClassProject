// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BaseBasicAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseBasicAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseBasicAIController(); 

protected:

	virtual void OnPossess(APawn* PossessedPawn) override;

	UFUNCTION()
		void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName PlayerKey;

	
};
