// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseWeapon.h"
#include "Actors/BaseLauncher.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h" 
#include "Art/BaseRifleAnimInstance.h"
#include "Components/BaseHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));
	//set the generate overlap events of the mesh to true
	GetMesh()->SetGenerateOverlapEvents(true);

	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChild->SetupAttachment(this->GetMesh(), "WeaponTransform");

	HealthComponent = CreateDefaultSubobject<UBaseHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetReferences();

	BindWeapAndAnimEvents();

	HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeath);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::Attacks()
{
	Weapon->Attacks();
}

void ABaseCharacter::SpecialAttack()
{
	Weapon->SpecialAttack();
}

void ABaseCharacter::Damaged() 
{
	AnimInstance->PlayDamaged();
}

void ABaseCharacter::PlayAttack()
{
	AnimInstance->PlayAttack();
}

void ABaseCharacter::PlayDeath()
{
	AnimInstance->PlayDeath();
}

void ABaseCharacter::AnimEnded()
{
	Weapon->AnimationEnded();
}

void ABaseCharacter::OwnerDied()
{
	Weapon->OwnerDied();
}

void ABaseCharacter::HandleDeath()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayDeath();
	OwnerDied();
}

void ABaseCharacter::SwapWeapons()
{
	if (WeaponClass == RifleClass)
	{
		WeaponClass = LauncherClass;
		SetReferences();
		BindWeapAndAnimEvents();
	}
	else
	{
		WeaponClass = RifleClass;
		SetReferences();
		BindWeapAndAnimEvents();
	}
}

void ABaseCharacter::SetReferences()
{
	WeaponChild->SetChildActorClass(WeaponClass);

	Weapon = Cast<ABaseWeapon>(WeaponChild->GetChildActor());

	GetMesh()->SetAnimInstanceClass(Weapon->WeaponSync.AnimInstance);

	AnimInstance = Cast<UBaseRifleAnimInstance>(GetMesh()->GetAnimInstance());
}

void ABaseCharacter::BindWeapAndAnimEvents()
{
	//if HealthComponent on damaged is bound to this class, unbind it then bind it again
	if (HealthComponent->OnDamaged.IsBound())
	{
		HealthComponent->OnDamaged.RemoveDynamic(this, &ABaseCharacter::Damaged); 
		HealthComponent->OnDamaged.AddDynamic(this, &ABaseCharacter::Damaged); 
	}
	else
		HealthComponent->OnDamaged.AddDynamic(this, &ABaseCharacter::Damaged);

	if (Weapon->OnAttack.IsBound())
	{
		Weapon->OnAttack.RemoveDynamic(this, &ABaseCharacter::PlayAttack);
		Weapon->OnAttack.AddDynamic(this, &ABaseCharacter::PlayAttack);
	}
	else
		Weapon->OnAttack.AddDynamic(this, &ABaseCharacter::PlayAttack); 

	if (AnimInstance->OnActionEnded.IsBound())
	{
		AnimInstance->OnActionEnded.RemoveDynamic(this, &ABaseCharacter::AnimEnded);
		AnimInstance->OnActionEnded.AddDynamic(this, &ABaseCharacter::AnimEnded);
	}
	else
	AnimInstance->OnActionEnded.AddDynamic(this, &ABaseCharacter::AnimEnded); 
}

bool ABaseCharacter::CanPickupHealth() const
{
	return false;
}

bool ABaseCharacter::ShouldPickupHealth() const
{
	return false;
}

