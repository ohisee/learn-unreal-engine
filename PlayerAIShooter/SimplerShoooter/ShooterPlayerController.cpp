// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    // always call Super
    Super::BeginPlay();

    hudScreen = CreateWidget(this, hudScreenClass);
    if (hudScreen != nullptr)
    {
        hudScreen->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    // always call Super
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("We have completed this task."));

    // remove heads up display screen
    if (hudScreen != nullptr)
    {
        hudScreen->RemoveFromViewport();
    }

    if (bIsWinner)
    {
        // player controller can own a widget
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        // player controller can own a widget
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    // restart the game
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
