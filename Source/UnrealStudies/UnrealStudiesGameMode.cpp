// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealStudiesGameMode.h"
#include "UnrealStudiesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealStudiesGameMode::AUnrealStudiesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
