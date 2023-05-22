// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BaseAI.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/GameResultsWidget.h"
#include "Actors/BasePlayer.h"

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

	APawn* ActivePlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	ActivePlayer = Cast<ABasePlayer>(ActivePlayerPawn);

	if (ActivePlayer)
	{
		ActivePlayer->OnDestroyed.AddDynamic(this, &ABaseGameMode::RemovePlayer);

		ActivePlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		ResultsWidget = CreateWidget<UGameResultsWidget>(ActivePlayerController, GameResultsWidgetClass);
	}
}

void ABaseGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	--CurrentEnemyCount;

	if (CurrentEnemyCount <= 0)
	{
		ResultsWidget->SetWin(); 
		ResultsWidget->AddToViewport(); 

		ActivePlayer->DisableInput(ActivePlayerController); 
		ActivePlayer->OnDestroyed.RemoveDynamic(this, &ABaseGameMode::RemovePlayer); 

		ActivePlayer->RemoveUI(); 
	}
}

void ABaseGameMode::RemovePlayer(AActor* DestroyedActor)
{
	ResultsWidget->AddToViewport();

	TArray<AActor*> FoundActors; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, FoundActors); 
	ABaseAI* AI = nullptr;
	for (AActor* Actor : FoundActors)
	{
		AI = Cast<ABaseAI>(Actor); 
		if (AI)
		{
			AI->WhenPlayerDies();
		}
	}

	ActivePlayerController->SetShowMouseCursor(true);
	ActivePlayerController->SetInputMode(FInputModeUIOnly());
	ActivePlayer->RemoveUI();
}
