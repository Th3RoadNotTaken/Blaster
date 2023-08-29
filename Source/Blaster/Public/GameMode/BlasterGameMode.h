// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

namespace MatchState
{
	extern BLASTER_API const FName Cooldown; // Match duration has been reached, display winner and begin cooldown timer
}

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ABlasterGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(class ABlasterCharacter* ElimmedCharacter, class ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;
	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;
	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	// Getting the level starting time as GetWorld()->GetTimeSeconds() will return the total time since main menu
	float LevelStartingTime = 0.f;

protected:

	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;

private:

	int32 CalculateFavourableRespawnPoint(TArray<AActor*> PlayerStarts, TArray<AActor*> BlasterActors);
	float CountdownTime = 0.f;

public:
	
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};
