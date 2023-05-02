// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseBullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
//if there are any includes for time, add them here. if not, comment "none found"
#include "TimerManager.h"
//include UGameplayStatics
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//set start with tick enabled to be false
	PrimaryActorTick.bStartWithTickEnabled = false;

	TimeToDestroy = 3.f;
	Damage = 1.f;

#pragma region SphereCollision
	//set a sphere collision component as the root component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	//set the collision preset to be OverlapAllDynamic
	SphereCollision->SetCollisionProfileName("OverlapAllDynamic");
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
#pragma endregion

#pragma region SphereMesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	//set the mesh transform to be 0.6 on the x, y, and z axis

	//Safely set the mesh to be that of the sphere mesh asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//if the mesh is found, set the SphereMesh to be that of the sphere mesh asset
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	SphereMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	//set mesh generate overlap event to be false
	SphereMesh->SetGenerateOverlapEvents(false);
	//Set the mesh's collision preset to be no collision
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SphereMesh->SetupAttachment(SphereCollision);

	//set the SphereMesh material to be that of M_FlatColor
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Art/M_FlatColor.M_FlatColor'"));
	//if the material is found, set the SphereMesh material to be that of M_FlatColor
	if (Material.Succeeded())
	{
		SphereMesh->SetMaterial(0, Material.Object);
	}
#pragma endregion

#pragma region ProjectileMovement
	//set movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//set projectile movement's initial speed to be 1800
	ProjectileMovement->InitialSpeed = 1800.f;
	//set the max speed to be 2000
	ProjectileMovement->MaxSpeed = 2000.f;
	//set projectile gravity scale to be 0
	ProjectileMovement->ProjectileGravityScale = 0.f;
#pragma endregion

	SetRootComponent(SphereCollision); 
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::HandleCollision);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseBullet::K2_DestroyActor, TimeToDestroy, false); 
}

void ABaseBullet::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	//use the apply damage function to apply damage to the other actor
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), nullptr);
	
	Destroy();
}

