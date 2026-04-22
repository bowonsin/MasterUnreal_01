// Copyright Epic Games, Inc. All Rights Reserved.

#include "MasterUnreal_01GameMode.h"
#include "MasterUnreal_01Character.h"
#include "UObject/ConstructorHelpers.h"

AMasterUnreal_01GameMode::AMasterUnreal_01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
