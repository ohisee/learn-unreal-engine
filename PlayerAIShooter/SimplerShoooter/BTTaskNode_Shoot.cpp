// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot Task");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController *AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter *AICharacterPawn = Cast<AShooterCharacter>(AIController->GetPawn());
    if (AICharacterPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AICharacterPawn->Shoot();
    return EBTNodeResult::Succeeded;
}
