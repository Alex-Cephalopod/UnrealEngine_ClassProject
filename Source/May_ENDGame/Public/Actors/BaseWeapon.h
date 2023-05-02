// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class MAY_ENDGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* WeaponMesh;

	//set up a pawn variable to store the pawn owner
	UPROPERTY()
		class APawn* PawnOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Create a UClass variable to store the bullet class ABaseBullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseBullet> BulletClass;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Attacks();

};
