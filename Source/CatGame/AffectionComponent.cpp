// Fill out your copyright notice in the Description page of Project Settings.


#include "AffectionComponent.h"

// Sets default values for this component's properties
UAffectionComponent::UAffectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAffectionComponent::BeginPlay()
{
	Super::BeginPlay();

	Thresholds.Sort();
	OnAffectionChanged.Broadcast(Affection, MaxAffection);
	
}

// Called every frame
void UAffectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float DecayFloor = GetDecayFloor();
	if (Affection <= DecayFloor) return;

	SetAffection(FMath::Max(Affection - DecayPerSecond * DeltaTime, DecayFloor));
}

void UAffectionComponent::AddAffection(float Amount)
{
	SetAffection(Affection + Amount);
}

void UAffectionComponent::SetAffection(float NewValue)
{
	const float OldValue = Affection;
	Affection = FMath::Clamp(NewValue, 0.f, MaxAffection);
	if (FMath::IsNearlyEqual(Affection, OldValue)) return;

	OnAffectionChanged.Broadcast(Affection, MaxAffection);
	CheckThresholds(Affection);
}

void UAffectionComponent::CheckThresholds(float NewValue)
{
	for (int32 i = FMath::Max(HighestThresholdReached + 1, 0); i < Thresholds.Num(); i++)
	{  
		if (NewValue < Thresholds[i]) break;
		HighestThresholdReached = i;
		OnAffectionThresholdReached.Broadcast(i);
	}
}

float UAffectionComponent::GetDecayFloor() const
{
	if (!Thresholds.IsValidIndex(HighestThresholdReached)) return 0.f;
	return Thresholds[HighestThresholdReached];
}

float UAffectionComponent::GetAffectionPercent() const
{
	return MaxAffection > 0.f? Affection / MaxAffection : 0.f;
}

