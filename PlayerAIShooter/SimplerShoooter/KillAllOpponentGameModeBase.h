// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplerShoooterGameModeBase.h"
#include "KillAllOpponentGameModeBase.generated.h"

/**
 * This is kill all opponent game mode class.
 */
UCLASS()
class SIMPLERSHOOOTER_API AKillAllOpponentGameModeBase : public ASimplerShoooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn *PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
