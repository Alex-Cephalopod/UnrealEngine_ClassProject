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
#include "Components/BaseEffectsComponent.h"
#include "Actors/BaseFireEffect.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionProfileName("Custom");
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChild->SetupAttachment(this->GetMesh(), "WeaponTransform");

	EffectsComponent = CreateDefaultSubobject<UBaseEffectsComponent>(TEXT("EffectsComponent"));
	EffectsComponent->SetupAttachment(GetMesh());
	EffectsComponent->SetRelativeLocation(FVector(0.f, 0.f, 140.f));

	HealthComponent = CreateDefaultSubobject<UBaseHealthComponent>(TEXT("HealthComponent"));


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetReferences();

	BindWeapAndAnimEvents();

	HealthComponent->OnDeathHealth.AddDynamic(this, &ABaseCharacter::HandleDeath);

	/*EffectsComponent->StartEffects(EEffects::EE_Burning, this);*/
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

void ABaseCharacter::PlayDamage()
{
	AnimInstance->PlayDamaged();
}

void ABaseCharacter::SpecialAttack()
{
	Weapon->SpecialAttack();
}

void ABaseCharacter::PlayDeath()
{
	AnimInstance->PlayDeath();
}

void ABaseCharacter::OwnerDied()
{
	Weapon->OwnerDied();
}

void ABaseCharacter::HandleDeath(float _Percent)
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

	if (!HealthComponent->OnDamageHealth.IsBound())
	{
		HealthComponent->OnDamageHealth.AddDynamic(AnimInstance, &UBaseRifleAnimInstance::PlayDamageWithFloat);
	}

	if (!Weapon->OnAttack.IsBound()) 
	{
		Weapon->OnAttack.AddDynamic(AnimInstance, &UBaseRifleAnimInstance::PlayAttack);
	}

	if (!AnimInstance->OnActionEnded.IsBound()) 
	{
		AnimInstance->OnActionEnded.AddDynamic(Weapon, &ABaseWeapon::AnimationEnded);
	}
}

bool ABaseCharacter::CanPickupHealth() const
{
	return false;
}

bool ABaseCharacter::ShouldPickupHealth() const
{
	return false;
}

