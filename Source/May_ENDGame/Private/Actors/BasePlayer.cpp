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
	//give camera component a default value
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

}
