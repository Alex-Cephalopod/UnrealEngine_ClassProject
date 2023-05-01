// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
//include spring arm component
#include "Camera/CameraComponent.h"
//include camera component
#include "GameFramework/SpringArmComponent.h"


ABasePlayer::ABasePlayer()
{
	//give spring arm component a default value
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	//raise up component by 60 units
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	SpringArmComp->bUsePawnControlRotation = true;
	//give camera component a default value
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

	//bind jump action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);

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
