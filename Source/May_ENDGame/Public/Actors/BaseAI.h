// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "Interfaces/IBaseEnemy.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class MAY_ENDGAME_API ABaseAI : public ABaseCharacter, public IIBaseEnemy 
{
	GENERATED_BODY()

public:

	ABaseAI();

	//create a blackboard object reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName AmmoKey;
	
protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void BindWeapAndAnimEvents() override;

	UFUNCTION()
		void WhenPlayerDies();

	UFUNCTION()
		void ActionEnded();

	UFUNCTION()
		void UpdateBlackboard(float _Current, float _Max);

	void Shoot() override;

	void AIReload() override;
};
