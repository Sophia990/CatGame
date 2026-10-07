#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AffectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnAffectionChanged,
	float, Affection,
	float, MaxAffection
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAffectionThresholdReached,
	int32, ThresholdIndex
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnHighestThresholdReached
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATGAME_API UAffectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAffectionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float Affection = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float MaxAffection = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float DecayPerSecond = 0.f;

	UPROPERTY(BlueprintAssignable, Category = "Affection")
	FOnAffectionChanged OnAffectionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Affection")
	FOnAffectionThresholdReached OnAffectionThresholdReached;

	UPROPERTY(BlueprintAssignable, Category = "Affection")
	FOnHighestThresholdReached OnHighestThresholdReached;
	
	UPROPERTY(EditAnywhere, Category = "Affection")
	TArray<float> Thresholds;

	UPROPERTY(BlueprintReadOnly, Category = "Affection")
	int32 HighestThresholdReached = -1;

	UFUNCTION(BlueprintCallable, Category = "Affection")
	void AddAffection (float Amount);

	UFUNCTION(BlueprintPure, Category = "Affection")
	float GetAffectionPercent() const;

protected:
	virtual void BeginPlay() override;

	void SetAffection(float NewValue);
	
	void CheckThresholds(float NewValue);
	
	float GetDecayFloor() const;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
