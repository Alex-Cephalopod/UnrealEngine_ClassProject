// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BaseHealthComponent.h"
#include "Widgets/HUDWidget.h"
#include "Blueprint/UserWidget.h"


ABasePlayer::ABasePlayer()
{
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 80.0f, 90.0f));
	SpringArmComp->TargetArmLength = 210.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	//add widget to viewport
	HUDWidget->AddToViewport();
}

bool ABasePlayer::CanPickupHealth() const
{
	return true;
}

bool ABasePlayer::ShouldPickupHealth() const
{
	return !HealthComponent->IsFullHealth();
}

void ABasePlayer::SetReferences()
{
	Super::SetReferences();
	PlayerController = Cast<APlayerController>(GetController());
	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("StandardAttack", IE_Pressed, this, &ABaseCharacter::Attacks);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &ABaseCharacter::SpecialAttack);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ABaseCharacter::SwapWeapons);

}

void ABasePlayer::MoveForward(float Value)
{
	FVector Forward = GetActorForwardVector(); 
	AddMovementInput(Forward, Value); 
}

void ABasePlayer::MoveRight(float Value)
{
	FVector Right = GetActorRightVector();
	AddMovementInput(Right, Value);
}

void ABasePlayer::Jump()
{
	Super::Jump();
}

void ABasePlayer::HandleDeath()
{
	Super::HandleDeath();
	DisableInput(PlayerController);
}

