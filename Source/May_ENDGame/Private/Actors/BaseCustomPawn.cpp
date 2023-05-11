// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCustomPawn.h"

// Sets default values
ABaseCustomPawn::ABaseCustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	

}

// Called when the game starts or when spawned
void ABaseCustomPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FRotator ABaseCustomPawn::GetBaseAimRotation() const
{
	return Super::GetBaseAimRotation();
}

