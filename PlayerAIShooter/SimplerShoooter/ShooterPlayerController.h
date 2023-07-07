// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * This is shooter player controller class.
 */
UCLASS()
class SIMPLERSHOOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f; // 5 seconds delay

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> hudScreenClass;

	// declare as a UPROPERTY because we need to keep hold of
	// this hudScreen pointer and can be garbage collected
	// correctly by using UPROPERTY
	UPROPERTY()
	class UUserWidget *hudScreen;

	FTimerHandle RestartTimer;
};
