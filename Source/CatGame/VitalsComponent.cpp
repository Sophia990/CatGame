// Fill out your copyright notice in the Description page of Project Settings.


#include "VitalsComponent.h"

// Sets default values for this component's properties
UVitalsComponent::UVitalsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVitalsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVitalsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentFullness <= 0.f)
	{
		return;
	}

	CurrentFullness -= DrainPerSecond * DrainMultiplier * DeltaTime;
	CurrentFullness = FMath::Max(CurrentFullness, 0.0f);

	OnFullnessChanged.Broadcast(CurrentFullness, MaxFullness);

	if (!bHasStarved && CurrentFullness <= 0.f)
	{
		OnStarved.Broadcast();
		bHasStarved = true;
	}
}

void UVitalsComponent::Eat(float Amount)
{
	CurrentFullness = FMath::Clamp(CurrentFullness + Amount, 0.f, MaxFullness);
	OnFullnessChanged.Broadcast(CurrentFullness, MaxFullness);
}

