// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BaseAI.h"

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, FoundActors);

	for (AActor* Actor : FoundActors)
	{
		Actor->OnDestroyed.AddDynamic(this, &ABaseGameMode::RemoveEnemy);
	}

	CurrentEnemyCount = FoundActors.Num();

	APawn* ActivePlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	ActivePlayer->OnDestroyed.AddDynamic(this, &ABaseGameMode::RemovePlayer);

}

void ABaseGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	CurrentEnemyCount--;

	if (CurrentEnemyCount > 0)
	{

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	}
}

void ABaseGameMode::RemovePlayer(AActor* DestroyedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Lose!"));

	TArray<AActor*> FoundActors; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, FoundActors); 
	ABaseAI* AI = nullptr;
	for (AActor* Actor : FoundActors)
	{
		AI = Cast<ABaseAI>(Actor); 
		AI->WhenPlayerDies();
	}
}
