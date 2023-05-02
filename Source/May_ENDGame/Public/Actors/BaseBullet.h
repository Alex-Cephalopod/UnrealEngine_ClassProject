// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"
//Declare a dynamic multicast delegate with one parameter of type AActor*

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventHappens, AActor*, OtherActor);

UCLASS()
class MAY_ENDGAME_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UProjectileMovementComponent* ProjectileMovement;
	
	//time variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToDestroy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION() 
		void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep,
			const FHitResult& SweepResult);

};
