// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "SlashMaximum/DebugMacros.h"

// Sets default values
AItem::AItem() //: Amplitude(0.25f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	// Re-assign root component to Item Mesh and default scence root will be garbage collected
	RootComponent = ItemMesh;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play called"));

	// print message to screen
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("Item OnScreen Message"));
	}

	/*UWorld* World = GetWorld();
	if (World != nullptr)
	{
		FVector Location = GetActorLocation();
		DrawDebugSphere(World, Location, 25.f, THIRTY, FColor::Red, false, 30.f);
	}*/

	/*if (World != nullptr)
	{
		FVector Forward = GetActorForwardVector();
		DrawDebugLine(World, Location, Location + Forward * 100.f, FColor::Red, true, -1.f, 0, 1.f);
	}*/

	/*UWorld* World = GetWorld();
	if (World != nullptr)
	{
		DrawDebugPoint(World, Location + Forward * 100.f, 15.f, FColor::Red, true);
	}*/

	/*if (World != nullptr)
	{
		DrawDebugBox(World, Location, FVector(10.f), FColor::Red, true, -1.f, 0, 1.f);
	}*/


	//UWorld* World = GetWorld();

	// set actor location before get action location to get the new location
	//SetActorLocation(FVector(0.f, 0.f, 50.f));
	//SetActorRotation(FRotator(0.f, 45.f, 0.f));

	//FVector Location = GetActorLocation();
	//FVector Forward = GetActorForwardVector(); // vector with lenght of 1 centimeter (cm)

	// macro is defined in SlashMaximum.h file
	//DRAW_SPHERE(Location); // semicolon is option for macro
	//DRAW_LINE(Location, Location + Forward * 100.f);
	//DRAW_POINT(Location + Forward * 100);
	//DRAW_SPHERE_COLOR(Location, FColor::Blue);
	//DRAW_VECTOR(Location, Location + Forward * 100.f);
	//DRAW_BOX(Location);

	int32 AvgInt = Average<int32>(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("Average of int32: %d"), AvgInt);

	float AvgFloat = Average<float>(3.98f, 7.86f);
	UE_LOG(LogTemp, Warning, TEXT("Average of float: %f"), AvgFloat);
}

// Called every frame
// Project settings -> search 'frame rate' -> select 'Fixed Frame Rate'
// DeltaTime is how much time has passed since previous frame, seconds per frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("DeltaTime : %f"), DeltaTime);

	// print message to screen
	if (GEngine != nullptr)
	{
		FString Name = GetName();
		// FString Message = FString::Printf(TEXT("Item Name : %f"), *DeltaTime);
		// must have * before FString
		FString Message = FString::Printf(TEXT("Item Name : %s"), *Name);
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, Message);

		UE_LOG(LogTemp, Warning, TEXT("Item Name : %s"), *Name);
	}

	// make movement frame rate independent, scale by DeltaTime
	// Movement rate in units of cm/s (centimeters per second) 
	//float MovementRate = 50.f;
	float RotationRate = 85.f;

	// Movement rate * DeltaTime (cm/s) * (s/frame) = (cm/frame)
	//AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	//AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));

	RunningTime += DeltaTime;

	// float Amplitude = 0.25f; // distance of traveling up and down
	// float SpeedUp = 5.f;
	// float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	// AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

	DRAW_SPHERE_SingleFrame(GetActorLocation());
	// GetActorForwardVector() returns vector with lenght of 1 centimeter (cm)
	DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);

	// mid point between the origin and the actor 
	FVector AvgVector = Average<FVector>(GetActorLocation(), FVector::ZeroVector);
	DRAW_POINT_SingleFrame(AvgVector);

	// try to rotate this actor
	FRotator ActorRotator = GetActorRotation();
	ActorRotator.Yaw = RotationRate * DeltaTime;
	AddActorWorldRotation(ActorRotator);
}

// blueprint pure function
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

// blueprint pure function
float AItem::TransformedCosin()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}
