#include "VitalsComponent.h"

UVitalsComponent::UVitalsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVitalsComponent::BeginPlay()
{
	Super::BeginPlay();
}

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

