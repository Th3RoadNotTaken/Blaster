// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUD/BlasterHUD.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 80000.f

class AWeapon;
class ABlasterCharacter;
class ABlasterPlayerController;
class ABlasterHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCombatComponent();
	friend class ABlasterCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void EquipWeapon(AWeapon* WeaponToEquip);

protected:
	
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);
	UFUNCTION()
	void OnRep_EquippedWeapon();

	void FireButtonPressed(bool bPressed);
	void Fire();
	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

private:

	ABlasterCharacter* Character;
	ABlasterPlayerController* Controller;
	ABlasterHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;
	UPROPERTY(Replicated)
	bool bAiming;
	
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed = 450.f;

	bool bFireButtonPressed;
	FVector HitTarget;

	/**
	* HUD and Crosshairs
	*/
	FHUDPackage HUDPackage;
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;
	bool bAimingAtPlayer;
	float CrosshairAtPlayerFactor;

	/** 
	* Automatic Fire
	*/
	FTimerHandle FireTimer;
	bool bCanFire = true;
	void StartFireTimer();
	void FireTimerFinished();

	/** 
	* Aiming and FOV
	*/
	// Field of view when not aiming; set to the camera's base FOV in BeginPlay
	float DefaultFOV;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoomedFOV = 30.f;
	float CurrentFOV;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);

public:	
		
};
