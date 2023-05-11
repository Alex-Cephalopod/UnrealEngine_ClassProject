// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Art/BaseRifleAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "BaseCustomPawn.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FWeaponDelegate);

//make a USTRUCT to hold the weapon data
USTRUCT(BlueprintType)
struct FWeaponSyncInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UBaseRifleAnimInstance> AnimInstance;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool Dead;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
		FWeaponDelegate OnAttack;

	UPROPERTY()
		TArray<ABaseBullet*> Bullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponSyncInfo WeaponSync;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseBullet> BulletClass;

public:	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual ABaseBullet* Attacks();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void SpecialAttack();

	UFUNCTION(BlueprintCallable, Category = "Function")
		bool CanShoot() const;

	UFUNCTION(BlueprintCallable, Category = "Function")
		void AnimationEnded();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void OwnerDied();

	UFUNCTION(BlueprintCallable, Category = "Function")
		FRotator GetBaseAimRotation() const;

};
