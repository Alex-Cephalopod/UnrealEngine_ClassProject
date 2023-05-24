// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Art/BaseRifleAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FWeaponDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponDelegateTwoParams, float , _CurrentAmmo, float, _MaxAmmo);

USTRUCT(BlueprintType)
struct FWeaponSyncInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UBaseRifleAnimInstance> AnimInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 WeaponIndex;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAmmo;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
		FWeaponDelegate OnAttack;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
		FWeaponDelegate OnReloadAnim;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
		FWeaponDelegateTwoParams OnAmmoUpdate;

	UPROPERTY()
		TArray<ABaseBullet*> Bullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponSyncInfo WeaponSync;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UHUDWidget> HUDWidgetClass;

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
		void ReloadAmmo();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void RequestReload();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void UseAmmo();

};
