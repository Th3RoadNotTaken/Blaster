// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BlasterGameMode.h"
#include "Character/BlasterCharacter.h"
#include "PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerState/BlasterPlayerState.h"
#include "GameState/BlasterGameState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

ABlasterGameMode::ABlasterGameMode()
{
	// Stays in WaitingToStart state until we call StartMatch
	bDelayedStart = true;
}

void ABlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void ABlasterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = WarmupTime + MatchTime + CooldownTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			RestartGame();
		}
	}
}

void ABlasterGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ABlasterPlayerController* BlasterPlayer = Cast<ABlasterPlayerController>(*It);
		if (BlasterPlayer)
		{
			BlasterPlayer->OnMatchStateSet(MatchState);
		}
	}
}

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	ABlasterPlayerState* AttackerPlayerState = AttackerController ? Cast<ABlasterPlayerState>(AttackerController->PlayerState) : nullptr;
	ABlasterPlayerState* VictimPlayerState = VictimController ? Cast<ABlasterPlayerState>(VictimController->PlayerState) : nullptr;
	ABlasterGameState* BlasterGameState = GetGameState<ABlasterGameState>();


	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState && BlasterGameState)
	{
		AttackerPlayerState->AddToScore(1.f);
		BlasterGameState->UpdateTopScore(AttackerPlayerState);
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDeaths(1);
	}

	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}
}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		TArray<AActor*> BlasterActors;
		UGameplayStatics::GetAllActorsOfClass(
			this,
			APlayerStart::StaticClass(),
			PlayerStarts
		);
		UGameplayStatics::GetAllActorsOfClass(
			this,
			ABlasterCharacter::StaticClass(),
			BlasterActors
		);

		int32 Selection = CalculateFavourableRespawnPoint(PlayerStarts, BlasterActors);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}

int32 ABlasterGameMode::CalculateFavourableRespawnPoint(TArray<AActor*> PlayerStarts, TArray<AActor*> BlasterActors)
{
	float MaxDistanceFromRespawn = -1.f;
	int32 Selection = 0;
	int32 Index = 0;
	for (auto PlayerStart : PlayerStarts)
	{
		float MinDistance = (PlayerStart->GetActorLocation() - BlasterActors[0]->GetActorLocation()).Size();
		for (auto BlasterActor : BlasterActors)
		{
			float Distance = (PlayerStart->GetActorLocation() - BlasterActor->GetActorLocation()).Size();
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
			}
		}
		if (MinDistance > MaxDistanceFromRespawn)
		{
			MaxDistanceFromRespawn = MinDistance;
			Selection = Index;
		}
		Index++;
	}
	return Selection;
}