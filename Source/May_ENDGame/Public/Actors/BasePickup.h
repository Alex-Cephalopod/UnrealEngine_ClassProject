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
	ABasePickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
		UParticleSystemComponent* ParticleSystem;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		virtual bool CanPickUp(AActor* OtherActor) const;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		virtual bool ShouldPickUp(AActor* OtherActor) const;

protected:
	
	virtual void BeginPlay() override;

public:	
	UFUNCTION(Category = "Function")
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Category = "Function")
		virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Function")
		virtual void PostPickup();

	UFUNCTION(Category = "Function")
		virtual void HandleNoPickup();

};
