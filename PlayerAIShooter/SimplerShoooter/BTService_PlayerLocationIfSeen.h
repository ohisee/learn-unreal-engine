// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

/**
 * This is behavior tree service player location if seen class.
 */
UCLASS()
class SIMPLERSHOOOTER_API UBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocationIfSeen();

protected:
	// from UBTService.h
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
