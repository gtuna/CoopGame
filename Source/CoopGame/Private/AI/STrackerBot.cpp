// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STrackerBot.h"

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

