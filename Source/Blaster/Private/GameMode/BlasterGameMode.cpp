// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BlasterGameMode.h"
#include "Character/BlasterCharacter.h"
#include "PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
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