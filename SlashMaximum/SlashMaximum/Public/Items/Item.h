// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SLASHMAXIMUM_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// EditDefaultsOnly - we can edit this property only in default blue print
	// BlueprintReadOnly - we can see this property in event graph and cannot be used on private variable 
	// BlueprintReadWrite - we can read and write this property in event graph
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	// EditInstanceOnly - we can an instance in the world but not in default blue print
	// EditAnywhere - we can edit anywhere in the instance in the world and in default blue print
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	// BlueprintCallable 
	// BlueprintPure - pure function 
	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCosin();

	template<typename T>
	T Average(T First, T Second);

private:
	// VisibleDefaultsOnly
	// VisibleInstanceOnly 
	// meta = (AllowPrivateAccess = "true") - expose a private variable to the event graph
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	// use UPROPERTY to mark this variable to participate Unreal Engine reflection system
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
};

template<typename T>
inline T AItem::Average(T First, T Second)
{
	return (First + Second) / 2;
}
