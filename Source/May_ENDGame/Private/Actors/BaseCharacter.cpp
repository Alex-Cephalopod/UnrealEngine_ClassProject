// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseWeapon.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h" 


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Move mesh down by 90 degrees, so it's at the correct rotation.
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	//rotate the caracter -90 degrees so it faces the correct direction
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));

	//set the weapon as a child actor component
	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChild->SetupAttachment(this->GetMesh(), "WeaponTransform");
	WeaponClass = ABaseWeapon::StaticClass();

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponChild->SetChildActorClass(ABaseWeapon::StaticClass()); 
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

