// Copyright Epic Games, Inc. All Rights Reserved.

#include "JWGameMode.h"
#include "AIMovement/Character/BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJWGameMode::AJWGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_BaseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
