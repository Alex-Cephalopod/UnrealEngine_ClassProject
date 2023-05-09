// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseStickyBomb.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABaseStickyBomb::ABaseStickyBomb()
{
	Damage = 3.f;
	DamageRadius = 750.f;
	CollisionSize = FVector(0.3f, 0.3f, 0.3f);

	SphereCollision->SetWorldScale3D(CollisionSize);

	//give the mesh the correct material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("MaterialInstanceConstant'/Game/Art/MI_FlatColor_Green.MI_FlatColor_Green'"));
	if (Material.Succeeded())
	{
		SphereMesh->SetMaterial(0, Material.Object);
	}
	 
}

void ABaseStickyBomb::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& SweepResult)
{
	//cast other comp to a skeletal mesh component
	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(OtherComp);
	//if the cast is successful
	if (SkeletalMesh)
	{
		//Super::HandleOverlap(OtherActor, OtherComp, SweepResult);
		ProjectileMovement->StopMovementImmediately();
		SetActorEnableCollision(false);
		TeleportTo(SweepResult.ImpactPoint, GetActorRotation());
		AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		DestroyTimerHandle.Invalidate();

	}
	else
	{
		switch (OtherComp->GetCollisionObjectType())
		{
			 case ECC_WorldStatic:
			 {
				 ProjectileMovement->StopMovementImmediately();
				 //stop the timer
				 GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
				 DestroyTimerHandle.Invalidate();

				 //call the teleport function that takes in a location and a rotation
				 TeleportTo(SweepResult.Location, GetActorRotation());

				 SphereCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseBullet::OnComponentBeginOverlap);

			 }
			 case ECC_WorldDynamic:

			 case ECC_Pawn:
			 {

			 }
		}
	}
}

void ABaseStickyBomb::SpecialAttack()
{
	//print a debug message
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Special Attack")); 

	//call apply radial damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr, TArray<AActor*>(), this, GetInstigatorController(), false, ECC_Visibility);

	Destroy();
}
