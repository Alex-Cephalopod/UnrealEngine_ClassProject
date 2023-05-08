// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseStickyBomb.h"
#include "Components/SphereComponent.h"

ABaseStickyBomb::ABaseStickyBomb()
{
	Damage = 3.f;
	CollisionSize = FVector(0.3f, 0.3f, 0.3f);

	SphereCollision->SetWorldScale3D(CollisionSize);

	//give the mesh the correct material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("MaterialInstanceConstant'/Game/Art/MI_FlatColor_Green.MI_FlatColor_Green'"));
	if (Material.Succeeded())
	{
		SphereMesh->SetMaterial(0, Material.Object);
	}
	 
}
