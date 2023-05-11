// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseBullet.h"
#include "Art/BaseRifleAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "Actors/BaseCustomPawn.h"

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

	CustomPawnOwner = Cast<ABaseCustomPawn>(GetParentActor());

	if (CustomPawnOwner == nullptr)
	{
		//print to screen in red that there is no custom pawn owner for this weapon in all caps
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO CUSTOM PAWN OWNER FOR THIS WEAPON"), true, FVector2D(2.f, 2.f));
		//thank you :)
	}
}

ABaseBullet* ABaseWeapon::Attacks()
{
	ABaseBullet* Bullet = nullptr;
	if (CanShoot()) //this for some reason throws a nullptr after repossessing
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