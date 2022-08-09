// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"

#include "GameFramework/GameStateBase.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	Health = 100;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);
	}
	
	DefaultHealth = Health;
}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	// Update health
	Health = FMath::Clamp(Health-Damage, 0.0f, DefaultHealth);

	UE_LOG(LogGameState, Log , TEXT("Health Changes: %s "), *FString::SanitizeFloat(Health));
}

