// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UCharacterOverlay;
class UAnnouncement;
class USniperScope;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:

	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;

	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
	TSubclassOf<UUserWidget> CharacterOverlayClass;
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;
	void AddCharacterOverlay();
	void HideCharacterOverlay();

	UPROPERTY(EditAnywhere, Category = "Scopes")
	TSubclassOf<UUserWidget> SniperScopeClass;
	UPROPERTY()
	USniperScope* SniperScopeWidget;
	void AddSniperScope();

	UPROPERTY(EditAnywhere, Category = "Announcements")
	TSubclassOf<UUserWidget> AnnouncementClass;
	UPROPERTY()
	UAnnouncement* Announcement;
	void AddAnnouncement();
	void HideAnnouncement();
	void SetAnnouncmentText(FString Text);
	void HideInfoText();
	void SetInfoText(FString Text);

protected:

	virtual void BeginPlay() override;

private:

	FHUDPackage HUDPackage;

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor);

public:

	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
	
};
