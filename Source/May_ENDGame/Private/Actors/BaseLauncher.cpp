// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseLauncher.h"
#include "Actors/BaseStickyBomb.h"

void ABaseLauncher::BeginPlay()
{
	Super::BeginPlay();
	BulletClass = ABaseStickyBomb::StaticClass();
}