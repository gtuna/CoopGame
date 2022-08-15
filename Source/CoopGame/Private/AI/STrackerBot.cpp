// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STrackerBot.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTrackerBot::ASTrackerBot()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();
	
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

