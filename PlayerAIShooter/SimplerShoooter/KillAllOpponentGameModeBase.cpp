// Fill out your copyright notice in the Description page of Project Settings.

#include "KillAllOpponentGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillAllOpponentGameModeBase::PawnKilled(APawn *PawnKilled)
{
    // always include calling this method in parent class using Super
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A pawn is out"));

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    // player is out
    if (PlayerController != nullptr)
    {
        bool bIsPlayerWinner = false; // player is not a winner
        // PlayerController->GameHasEnded(nullptr, bIsPlayerWinner);
        EndGame(bIsPlayerWinner);
    }

    // for loop over ShooterAI in World
    for (AShooterAIController *Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        // if IsOut is false
        if (!Controller->IsOut())
        {
            return;
        }
    }
    // player is winner
    EndGame(true);
}

void AKillAllOpponentGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        // if it is player controller and player is winner
        // if it is AI controller and AI is winner
        // otherwise bIsWinnder is false
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        // set end game focus actor to controller's pawn, the controller which wins the game
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
