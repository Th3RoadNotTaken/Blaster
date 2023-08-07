// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Casing.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Casing Mesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	ShellEjectionImpulse = 3.f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();
	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);
	CasingMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	CasingMesh->SetNotifyRigidBodyCollision(true);
}

void ACasing::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound && !bShellHitGround)
	{
		bShellHitGround = true;
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ShellSound,
			GetActorLocation()
		);
	}
	UWorld* World = GetWorld();
	GetWorldTimerManager().SetTimer(
		ShellDestroyTimerHandle,
		this, 
		&ThisClass::DestroyShell,
		ShellDestroyDelay,
		false);
}

void ACasing::DestroyShell()
{
	GetWorldTimerManager().ClearTimer(ShellDestroyTimerHandle);
	Destroy();
}

void ACasing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

