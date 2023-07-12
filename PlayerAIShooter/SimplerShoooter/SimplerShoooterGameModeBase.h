// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimplerShoooterGameModeBase.generated.h"

/**
 * This is root game mode class.
 */
UCLASS()
class SIMPLERSHOOOTER_API ASimplerShoooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn *PawnKilled);
};
