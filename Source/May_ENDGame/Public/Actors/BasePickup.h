// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS(Abstract)
class MAY_ENDGAME_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* CollisionBox;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		virtual bool CanPickUp(AActor* OtherActor) const;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		virtual bool ShouldPickUp(AActor* OtherActor) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Category = "Pickup")
		virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		virtual void PostPickup();

};
