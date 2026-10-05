// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VitalsComponent.h"
#include "CoreMinimal.h"
#include "CatGameCharacter.h"
#include "PreyActor.h"
#include "CatCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfLives);

UCLASS()
class CATGAME_API ACatCharacter : public ACatGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vitals")
	TObjectPtr<UVitalsComponent> Vitals;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cat")
	TObjectPtr<APreyActor> CarriedPrey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Vitals")
	int32 MaxLives = 3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vitals")
	int32 Lives = 3;

	UPROPERTY(BlueprintAssignable, Category="Vitals")
	FOnOutOfLives OnOutOfLives;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float BiteInvulnerabilityDuration = 1.25f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	bool bIsBiteInvulnerable = false;
	FTimerHandle BiteInvulnerabilityTimer;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeBite(AActor* AttackingDog);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndBiteInvulnerability();

	UFUNCTION(BlueprintCallable, Category = "Cat")
	void DropCarriedPrey();

	UFUNCTION(BlueprintPure, Category = "Cat")
	bool CanPickUpPrey() const { return !CarriedPrey && !bIsBiteInvulnerable; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
