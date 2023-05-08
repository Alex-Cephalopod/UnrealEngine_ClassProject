// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseBullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TimeToDestroy = 3.f;
	Damage = 1.f;
	MeshSize = FVector(0.6f, 0.6f, 0.6f);
	CollisionSize = FVector(0.2f, 0.2f, 0.2f);

#pragma region SphereCollision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionProfileName("OverlapAllDynamic");
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetWorldScale3D(CollisionSize);
#pragma endregion

#pragma region SphereMesh_And_Material
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	SphereMesh->SetRelativeScale3D(MeshSize);
	SphereMesh->SetGenerateOverlapEvents(false);
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SphereMesh->SetupAttachment(SphereCollision);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Art/M_FlatColor.M_FlatColor'"));
	if (Material.Succeeded())
	{
		SphereMesh->SetMaterial(0, Material.Object);
	}
#pragma endregion

#pragma region ProjectileMovement
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1800.f;
	ProjectileMovement->MaxSpeed = 2000.f;
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
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), nullptr);
	
	Destroy();
}

