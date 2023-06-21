// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SIMPLERSHOOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunActor();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent *RootSceneComponent;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent *SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere)
	class USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *ImpactEffectParticleSystem;

	UPROPERTY(EditAnywhere)
	class USoundBase *ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f; // 10 meters

	UPROPERTY(EditAnywhere)
	float DamageAmount = 10.f;

	bool GunTrace(FHitResult &HitResult, FVector &ShotDirection);

	AController *GetOwnerController() const;
};
