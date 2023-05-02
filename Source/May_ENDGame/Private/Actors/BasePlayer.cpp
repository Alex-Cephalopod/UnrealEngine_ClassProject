// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
//include spring arm component
#include "Camera/CameraComponent.h"
//include camera component
#include "GameFramework/SpringArmComponent.h"


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

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind axis to look up and look right
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	//button input actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	//add an input for stop jumping
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("StandardAttack", IE_Pressed, this, &ABaseCharacter::Attacks);

}

void ABasePlayer::MoveForward(float Value)
{
	//get the forward vector of the player
	FVector Forward = GetActorForwardVector(); 
	//move the player forward
	AddMovementInput(Forward, Value); 
}

void ABasePlayer::MoveRight(float Value)
{
	//get the right vector of the player
	FVector Right = GetActorRightVector();
	//move the player right
	AddMovementInput(Right, Value);
}

void ABasePlayer::Jump()
{
	//call the jump function
	Super::Jump();

}
