// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseBullet.h"
#include "Art/BaseRifleAnimInstance.h"
#include "Actors/BasePlayer.h"
#include "GameFramework/Pawn.h"
#include "Actors/BaseCustomPawn.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
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
	return !Animating && !Dead;
}

void ABaseWeapon::AnimationEnded()
{
	Animating = false;
}

void ABaseWeapon::OwnerDied()
{
	Dead = true;
}

