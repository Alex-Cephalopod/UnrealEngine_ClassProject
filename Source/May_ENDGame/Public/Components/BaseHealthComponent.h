// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAY_ENDGAME_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseHealthComponent();

	//create float called MaxHealth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

private:
	//create float called CurrentHealth
	UPROPERTY()
		float CurrentHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame

	//create function called InitHealth
	UFUNCTION(BlueprintCallable, Category = "Health")
		void InitHealth();

	//create a function called DamageHappened that takes in a Damaged Actor, Damage, Damage Type, Instigated By, and Damage Causer
	UFUNCTION(BlueprintCallable, Category = "Health")
		void DamageHappened(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);
};
