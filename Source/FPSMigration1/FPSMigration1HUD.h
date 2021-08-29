// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSMigration1HUD.generated.h"

UCLASS()
class AFPSMigration1HUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSMigration1HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

