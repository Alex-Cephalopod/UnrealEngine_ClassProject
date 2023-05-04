// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseWeapon.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h" 
#include "Art/BaseRifleAnimInstance.h"
#include "Components/BaseHealthComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));

	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChild->SetupAttachment(this->GetMesh(), "WeaponTransform");

	HealthComponent = CreateDefaultSubobject<UBaseHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponClass = ABaseWeapon::StaticClass();
	WeaponChild->SetChildActorClass(WeaponClass);

	Weapon = Cast<ABaseWeapon>(WeaponChild->GetChildActor());

	AnimInstance = Cast<UBaseRifleAnimInstance>(GetMesh()->GetAnimInstance());

	HealthComponent->OnDamaged.AddDynamic(this, &ABaseCharacter::Damaged);

	Weapon->OnAttack.AddDynamic(this, &ABaseCharacter::PlayAttack);

	AnimInstance->OnActionEnded.AddDynamic(this, &ABaseCharacter::AnimEnded);
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

void ABaseCharacter::Damaged() 
{
	AnimInstance->PlayDamaged();
}

void ABaseCharacter::PlayAttack()
{
	AnimInstance->PlayAttack();
}

void ABaseCharacter::AnimEnded()
{
	Weapon->AnimationEnded();
}

