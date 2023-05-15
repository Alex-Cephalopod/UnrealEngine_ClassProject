// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BaseHealthComponent.h"
#include "Widgets/HUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Actors/BaseWeapon.h"


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
	HUDWidget->AddToViewport();

	HealthComponent->OnDamageHealth.AddDynamic(HUDWidget, &UHUDWidget::SetHealth);
	HealthComponent->OnDeathHealth.AddDynamic(HUDWidget, &UHUDWidget::SetHealth);
	HealthComponent->OnHealed.AddDynamic(HUDWidget, &UHUDWidget::SetHealth);
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
	if (!HUDWidget)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	}
}

FRotator ABasePlayer::GetBaseAimRotation() const
{
	FVector Hit;
	FVector EndPoint;
	FVector Destination;
	if (HUDWidget->GetEnd(Hit, EndPoint))
	{
		Destination = Hit;
	}
	else
	{
		Destination = EndPoint;
	}

	Destination -= Weapon->WeaponMesh->GetSocketLocation("MuzzleFlashSocket");

	return Destination.Rotation(); 
}

void ABasePlayer::BindWeapAndAnimEvents()
{
	Super::BindWeapAndAnimEvents();

	if (!AnimInstance->OnDeathEnded.IsBound())
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABasePlayer::K2_DestroyActor);
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnTo", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABasePlayer::StopJumping);
	PlayerInputComponent->BindAction("StandardAttack", IE_Pressed, this, &ABasePlayer::Attacks);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &ABasePlayer::SpecialAttack);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ABasePlayer::SwapWeapons);

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

void ABasePlayer::HandleDeath(float _Percent)
{
	Super::HandleDeath(_Percent);
	DisableInput(PlayerController);
}

