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

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("MaterialInstanceConstant'/Game/Art/MI_FlatColor_Green.MI_FlatColor_Green'"));
	if (Material.Succeeded())
	{
		SphereMesh->SetMaterial(0, Material.Object);
	}
	 
}

void ABaseStickyBomb::HandleOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& SweepResult)
{
	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(OtherComp);

	if (SkeletalMesh)
	{
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

				 GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
				 DestroyTimerHandle.Invalidate();

				 TeleportTo(SweepResult.Location, GetActorRotation());

				 SphereCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseBullet::OnComponentBeginOverlap);

			 }
		}
	}
}

void ABaseStickyBomb::SpecialAttack()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(),
		DamageRadius, nullptr, TArray<AActor*>(), this, GetInstigatorController(),
		false, ECC_Visibility);

	Destroy();
}
