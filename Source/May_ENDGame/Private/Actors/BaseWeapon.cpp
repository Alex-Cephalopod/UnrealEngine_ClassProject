// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseBullet.h"
#include "Art/BaseRifleAnimInstance.h"
#include "Actors/BasePlayer.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Animating = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	BulletClass = ABaseBullet::StaticClass(); 
	PawnOwner = Cast<APawn>(GetParentActor()); 
}

ABaseBullet* ABaseWeapon::Attacks()
{
	ABaseBullet* Bullet = nullptr;
	if (CanShoot()) //this for some reason throws a nullptr after repossessing
	{
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Instigator = PawnOwner; 

		Bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletClass, WeaponMesh->GetSocketLocation("MuzzleFlashSocket"), GetBaseAimRotation(), SpawnParams);

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

FRotator ABaseWeapon::GetBaseAimRotation() const
{
	//if PawnOwner is not of ABasePlayer, then return the rotation of the weapon
	if (Cast<ABasePlayer>(PawnOwner->GetParentActor()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I did it")));
		return PawnOwner->GetBaseAimRotation();
	}
	else {
		FRotator Rotate = PawnOwner->GetBaseAimRotation();
		return Rotate; 
		
	}
}
