// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/BlasterGameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerState/BlasterPlayerState.h"

void ABlasterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterGameState, TopScoringPlayers);
}

void ABlasterGameState::UpdateTopScore(ABlasterPlayerState* ScoringPlayer)
{
	float PlayerScore = ScoringPlayer->GetScore();
	
	if (TopScoringPlayers.Num() <= 3)
	{
		TopScoringPlayers.AddUnique(ScoringPlayer);
	}
	else
	{
		for (int i = TopScoringPlayers.Num() - 1; i >= 0; i--)
		{
			if (PlayerScore > TopScoringPlayers[i]->GetScore())
			{
				if (i == TopScoringPlayers.Num() - 1)
				{
					TopScoringPlayers[i] = ScoringPlayer;
				}
				else
				{
					TopScoringPlayers[i + 1] = TopScoringPlayers[i];
					TopScoringPlayers[i] = ScoringPlayer;
				}
			}
		}
	}
}