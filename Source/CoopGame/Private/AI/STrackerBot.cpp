// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STrackerBot.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

// Sets default values
ASTrackerBot::ASTrackerBot()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	bUseVelocityChange = false;
	MovementForce = 1000;
	RequiredDistanceToTarget = 100;
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();

	NextPathPoint = GetNextPathPoint();
}

FVector ASTrackerBot::GetNextPathPoint()
{
	// hack to get player location
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this,0);
	
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn );

	if( NavigationPath->PathPoints.Num() > 1)
	{
		// return next point in the path
		return  NavigationPath->PathPoints[1];
	}

	// failed to find path
	return GetActorLocation();
	
}

void ASTrackerBot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float DistanceToTarget = (GetActorLocation() -NextPathPoint).Size();
	
	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		// Keep moving towards next target
		
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();

		ForceDirection *= MovementForce;
		
		MeshComp->AddForce(ForceDirection, NAME_None, bUseVelocityChange);
	}

}

