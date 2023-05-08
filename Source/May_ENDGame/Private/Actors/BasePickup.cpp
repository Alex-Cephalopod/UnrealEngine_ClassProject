// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	/*GetWorld()->GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BasePickup"));*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("OverlapAllDynamic"); 
	CollisionBox->SetGenerateOverlapEvents(true); 
	SetRootComponent(CollisionBox);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
}

bool ABasePickup::CanPickUp(AActor* OtherActor, bool yes) const
{
	return yes;
}

void ABasePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickUp(OtherActor) == true)
	{
		HandlePickup(OtherActor, SweepResult);
		PostPickup();
	}
}

void ABasePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{

}

void ABasePickup::PostPickup()
{
	Destroy();
}

