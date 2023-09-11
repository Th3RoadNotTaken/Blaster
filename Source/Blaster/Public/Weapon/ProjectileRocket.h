// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Projectile.h"
#include "ProjectileRocket.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileRocket : public AProjectile
{
	GENERATED_BODY()

public:

	AProjectileRocket();
	
protected:

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Radial Properties")
	float DamageInnerRadius = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Radial Properties")
	float DamageOuterRadius = 500.f;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RocketMesh;
};
