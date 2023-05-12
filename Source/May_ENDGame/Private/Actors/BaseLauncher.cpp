// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseLauncher.h"
#include "Actors/BaseStickyBomb.h"

ABaseLauncher::ABaseLauncher()
{

}

void ABaseLauncher::BeginPlay()
{
	Super::BeginPlay();
	BulletClass = ABaseStickyBomb::StaticClass();
}

ABaseBullet* ABaseLauncher::Attacks()
{
	ABaseBullet* Bullet = Super::Attacks();
	if (Bullet)
	{
		Bullets.Add(Bullet);
		Bullet->OnDestroyed.AddDynamic(this, &ABaseLauncher::RemoveDeadBullet);
		return Bullet;
	}
	else {
		return Bullet;
	}
}

void ABaseLauncher::SpecialAttack()
{
	
	for (int i = Bullets.Num() - 1; i >= 0; i--)
	{
		Bullets[i]->SpecialAttack();
	}
	Bullets.Empty();
}

void ABaseLauncher::RemoveDeadBullet(AActor* DestroyedBullet)
{
	ABaseBullet* BulletTemp = Cast<ABaseBullet>(DestroyedBullet);
	if (BulletTemp)
	{
		Bullets.Remove(BulletTemp);
	}
}
