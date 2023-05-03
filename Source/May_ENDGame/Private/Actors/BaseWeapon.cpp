// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Actors/BaseBullet.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Animating = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	//set the mesh of the weapon
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshAsset(TEXT("SkeletalMesh'/Game/END_Starter/Guns/Rifle/SK_Rifle.SK_Rifle'"));

	//set the mesh of the weapon, but unsafe
	WeaponMesh->SetSkeletalMesh(WeaponMeshAsset.Object);

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	BulletClass = ABaseBullet::StaticClass();
	//cast the parent actor to a pawn and store it in the pawn owner variable
	PawnOwner = Cast<APawn>(GetParentActor());

	if (PawnOwner != nullptr)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn Owner"));
	}
	
}

void ABaseWeapon::Attacks()
{
	//use the spawn actor function to spawn a projectile of bullet class, the spawn transform will be the GetActorTransform, and the instigator will be the pawn owner
	//GetWorld()->SpawnActor<ABullet>(BulletClass, GetActorTransform(), GetInstigator()); 
	if (CanShoot())
	{
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Instigator = PawnOwner; 
		SpawnParams.Owner = PawnOwner->GetController(); 

		GetWorld()->SpawnActor<ABaseBullet>(BulletClass, WeaponMesh->GetSocketLocation("MuzzleFlashSocket"), PawnOwner->GetBaseAimRotation(), SpawnParams); 

		Animating = true;

		OnAttack.Broadcast();
	}
	
}

bool ABaseWeapon::CanShoot() const
{
	return !Animating;
}

void ABaseWeapon::AnimationEnded()
{
	Animating = false;
}



