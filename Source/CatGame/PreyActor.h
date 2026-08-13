// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PreyActor.generated.h"

class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class CATGAME_API APreyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreyActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prey")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prey")
	TObjectPtr<USphereComponent> CatchSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prey")
	TObjectPtr<USphereComponent> NoticeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Prey")
	float FoodValue = 25.f;

	UFUNCTION(BlueprintCallable, Category = "Prey")
	void GetCaught();

	UFUNCTION(BlueprintPure, Category = "Prey")
	bool IsCarried() const { return bIsCarried; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Prey")
	bool bIsCarried = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
