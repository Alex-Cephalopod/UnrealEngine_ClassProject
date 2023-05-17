// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseBullet.h"
#include "Art/BaseRifleAnimInstance.h"
#include "Actors/BasePlayer.h"
#include "GameFramework/Pawn.h"
#include "Actors/BaseCustomPawn.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Animating = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	BulletClass = ABaseBullet::StaticClass(); 
	PawnOwner = Cast<APawn>(GetParentActor()); 
	ReloadAmmo();
}

ABaseBullet* ABaseWeapon::Attacks()
{
	ABaseBullet* Bullet = nullptr;
	if (CanShoot())
	{
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Instigator = PawnOwner; 

		Bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletClass, WeaponMesh->GetSocketLocation("MuzzleFlashSocket"), PawnOwner->GetBaseAimRotation(), SpawnParams);

		Animating = true;

		OnAttack.Broadcast();

		UseAmmo();

		return Bullet;
	}
	else
	{
		return Bullet;
	}
}

void ABaseWeapon::SpecialAttack()
{
	//do nothing
}

bool ABaseWeapon::CanShoot() const
{
	return !Animating && !Dead && (CurrentAmmo > 0.f);
}

void ABaseWeapon::AnimationEnded()
{
	Animating = false;
}

void ABaseWeapon::OwnerDied()
{
	Dead = true;
}

void ABaseWeapon::ReloadAmmo()
{
	CurrentAmmo = MaxAmmo;
	OnAmmoUpdate.Broadcast(CurrentAmmo, MaxAmmo);
}

void ABaseWeapon::RequestReload()
{
	if (Animating == false)
	{
		Animating = true;
		OnReloadAnim.Broadcast();
	}
}

void ABaseWeapon::UseAmmo()
{
	CurrentAmmo -= 1.f;
	CurrentAmmo = FMath::Clamp(CurrentAmmo, 0.f, MaxAmmo);
	OnAmmoUpdate.Broadcast(CurrentAmmo, MaxAmmo);
}
