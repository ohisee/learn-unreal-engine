// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    AAIController *AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return;
    }

    bool LineOfSight = AIController->LineOfSightTo(PlayerPawn);
    UBlackboardComponent *BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (BlackboardComponent != nullptr)
    {
        if (LineOfSight)
        {
            // BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
            // changed to SetValueAsObject when going over animation offset
            BlackboardComponent->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
        }
        else
        {
            BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
        }
    }
}
