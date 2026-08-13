// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VitalsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnFullnessChanged,
	float, CurrentFullness,
	float, MaxFullness
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarved);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATGAME_API UVitalsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVitalsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vitals")
	float MaxFullness = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vitals")
	float CurrentFullness = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vitals")
	float DrainPerSecond = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitals")
	float DrainMultiplier = 1.f;

	UPROPERTY(BlueprintReadOnly, Category = "Vitals")
	bool bHasStarved = false;

	UPROPERTY(BlueprintAssignable, Category = "Vitals")
	FOnFullnessChanged OnFullnessChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Vitals")
	FOnStarved OnStarved;

	UFUNCTION(BlueprintCallable)
	void Eat(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
