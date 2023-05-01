// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseBullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//set start with tick enabled to be false
	PrimaryActorTick.bStartWithTickEnabled = false;

	//set a sphere collision component as the root component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	//set the collision preset to be OverlapAllDynamic
	SphereCollision->SetCollisionProfileName("OverlapAllDynamic");
	SphereCollision->SetGenerateOverlapEvents(true);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	//set the mesh transform to be 0.6 on the x, y, and z axis
	SphereMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	//set mesh generate overlap event to be false
	SphereMesh->SetGenerateOverlapEvents(false);
	//Set the mesh's collision preset to be no collision
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereMesh->SetupAttachment(SphereCollision);

	//set movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//set projectile movement's initial speed to be 1800
	ProjectileMovement->InitialSpeed = 1800.f;
	//set the max speed to be 2000
	ProjectileMovement->MaxSpeed = 2000.f;
	//set projectile gravity scale to be 0
	ProjectileMovement->ProjectileGravityScale = 0.f;

	SetRootComponent(SphereCollision); 
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::HandleCollision);
}

void ABaseBullet::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	Destroy();
}

