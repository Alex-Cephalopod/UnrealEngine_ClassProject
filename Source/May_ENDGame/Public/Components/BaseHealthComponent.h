// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FHealthComponentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponentDelegateOneParam, float, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAY_ENDGAME_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthComponentDelegate OnDamageNoParam;

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthComponentDelegateOneParam OnDamageHealth;

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthComponentDelegateOneParam OnDeathHealth;

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthComponentDelegateOneParam OnHealed;

private:

	UPROPERTY()
		float CurrentHealth;

protected:

	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Health")
		void InitHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void DamageHappened(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool IsFullHealth() const;
};
