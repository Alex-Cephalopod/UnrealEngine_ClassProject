// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle DestroyTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToDestroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MeshSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CollisionSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION() 
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		virtual void HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Function")
		virtual void SpecialAttack();

};
