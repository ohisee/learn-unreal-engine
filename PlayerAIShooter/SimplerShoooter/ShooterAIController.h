// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * This is AI controller class.
 */
UCLASS()
class SIMPLERSHOOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// if this AI shooter is out
	bool IsOut() const;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree *AIBehaviorTree;
};
