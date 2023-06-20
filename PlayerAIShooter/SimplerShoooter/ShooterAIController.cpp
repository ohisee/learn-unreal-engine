// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehaviorTree != nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
        UBlackboardComponent *BlackboardComponent = GetBlackboardComponent();
        BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

        // this is pawn we are currently controlling
        APawn *AIPawn = GetPawn();
        BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move to UBTService_PlayerLocation and UBTService_PlayerLocationIfSeen
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    // UBlackboardComponent *BlackboardComponent = GetBlackboardComponent();
    // bool LineOfSight = LineOfSightTo(PlayerPawn);
    // if (LineOfSight)
    // {
    //     BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    //     BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    // }
    // else
    // {
    //     // clear player location
    //     BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
    // }

    // Replace this functionality with AI behavior tree
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    // bool LineOfSight = LineOfSightTo(PlayerPawn);
    // if (LineOfSight)
    // {
    //     // SetFocus
    //     SetFocus(PlayerPawn);
    //     // MoveTo
    //     float AcceptanceRadius = 200.f;
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    // }
    // else
    // {
    //     // AI does not follow the player when AI is not in line of sight
    //     // ClearFocus
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     // StopMovement
    //     StopMovement();
    // }
}

bool AShooterAIController::IsOut() const
{
    AShooterCharacter *ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsOut();
    }
    return true;
}
