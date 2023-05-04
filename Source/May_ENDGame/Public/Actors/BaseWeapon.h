// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FWeaponDelegate);

UCLASS()
class MAY_ENDGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY()
		class APawn* PawnOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool Animating;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
		FWeaponDelegate OnAttack;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseBullet> BulletClass;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Attacks();

	UFUNCTION(BlueprintCallable, Category = "Function")
		bool CanShoot() const;

	UFUNCTION(BlueprintCallable, Category = "Function")
		void AnimationEnded();

};
