// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VitalsComponent.h"
#include "CoreMinimal.h"
#include "CatGameCharacter.h"
#include "PreyActor.h"
#include "CatCharacter.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
