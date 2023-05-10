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
	
	//write a reverse for loop
	for (int i = Bullets.Num() - 1; i >= 0; i--)
	{
		Bullets[i]->SpecialAttack();
	}
	//clear Bullets
	Bullets.Empty();
}

void ABaseLauncher::RemoveDeadBullet(AActor* DestroyedBullet)
{
	//cast to ABaseBullet
	ABaseBullet* BulletTemp = Cast<ABaseBullet>(DestroyedBullet);
	if (BulletTemp)
	{
		//remove from Bullets
		Bullets.Remove(BulletTemp);
	}
	else
	{
		//print "How did I get here?"
		UE_LOG(LogTemp, Warning, TEXT("How did I get here?"));
		//also on the screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("How did I get here?")));
	}
}
