// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSMigration1GameMode.h"
#include "FPSMigration1HUD.h"
#include "FPSMigration1Character.h"
#include "UObject/ConstructorHelpers.h"

AFPSMigration1GameMode::AFPSMigration1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSMigration1HUD::StaticClass();
}
