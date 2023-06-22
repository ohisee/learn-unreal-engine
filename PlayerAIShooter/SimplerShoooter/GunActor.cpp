// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGunActor::AGunActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	SetRootComponent(RootSceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	SkeletalMeshComponent->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// handles pulling trigger
void AGunActor::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("Pull Trigger"));
	UGameplayStatics::SpawnEmitterAttached(
		MuzzleFlashParticleSystem, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));

	UGameplayStatics::SpawnSoundAttached(MuzzleSound, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));

	FHitResult OutHitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(OutHitResult, ShotDirection);

	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), OutHitResult.Location, 10.f, FColor::Red, false, 1.f);
		// impact effect
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ImpactEffectParticleSystem,
			OutHitResult.Location,
			ShotDirection.Rotation());
		// impact sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHitResult.Location);

		AActor *ActorGotHit = OutHitResult.GetActor();
		if (ActorGotHit != nullptr)
		{
			FPointDamageEvent DamageEvent(DamageAmount, OutHitResult, ShotDirection, nullptr);
			// get controller from owner pawn
			AController *OwnerController = GetOwnerController();
			if (OwnerController != nullptr)
			{
				ActorGotHit->TakeDamage(DamageAmount, DamageEvent, OwnerController, this);
			}
		}
	}

	// Draw debug
	// DrawDebugCamera(
	// 	GetWorld(),
	// 	Location,
	// 	Rotation,
	// 	90,
	// 	2,
	// 	FColor::Red,
	// 	true);
}

// get trace
bool AGunActor::GunTrace(FHitResult &HitResult, FVector &ShotDirection)
{
	// get controller from owner pawn
	AController *OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;
	// get player's view point through camera, out parameters
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	// set to ShotDirection out parameter
	ShotDirection = -Rotation.Vector();

	FVector EndPoint = Location + Rotation.Vector() * MaxRange;

	// avoid shooting to yourself
	FCollisionQueryParams Params;
	// ignore gun
	Params.AddIgnoredActor(this);
	// ignore the owner of gun
	Params.AddIgnoredActor(GetOwner());

	// look into project's config folder, DefaultEngine.ini filer, search for Channel
	// DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Block,bTraceType=True,bStaticObject=False,Name="Bullet")
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Location,
		EndPoint,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params);

	return bSuccess;
}

AController *AGunActor::GetOwnerController() const
{
	// get owner pawn, shooter character is a APawn type
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}

	// get controller from owner pawn
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		return nullptr;
	}

	return OwnerController;
}
