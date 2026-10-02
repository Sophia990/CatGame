// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATGAME_API UAffectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAffectionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float Affection = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float MaxAffection = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affection")
	float DecayPerSecond = 0.3f;

	UPROPERTY(BlueprintAssignable, Category = "Affection")
	FOnAffectionChanged OnAffectionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Affection")
	FOnAffectionThresholdReached OnAffectionThresholdReached;
	
	UPROPERTY(EditAnywhere, Category = "Affection")
	TArray<float> Thresholds;

	UPROPERTY(BlueprintReadOnly, Category = "Affection")
	int32 HighestThresholdReached = -1;

	UFUNCTION(BlueprintCallable, Category = "Affection")
	void AddAffection (float Amount);

	UFUNCTION(BlueprintPure, Category = "Affection")
	float GetAffectionPercent() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetAffection(float NewValue);
	
	void CheckThresholds(float NewValue);
	
	float GetDecayFloor() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
