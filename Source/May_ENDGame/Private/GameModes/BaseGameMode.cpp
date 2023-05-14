// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BaseAI.h"

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Get All Actors of Class
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, FoundActors);

	//write a for each loop to bind RemoveEnemy() to OnDestroyed
	for (AActor* Actor : FoundActors)
	{
		Actor->OnDestroyed.AddDynamic(this, &ABaseGameMode::RemoveEnemy);
	}

	CurrentEnemyCount = FoundActors.Num();

}

void ABaseGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	CurrentEnemyCount--;

	if (CurrentEnemyCount > 0)
	{

	}
	else
	{
		//print to screen debug message "You Win!"
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	}
}
