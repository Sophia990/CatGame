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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsBiteInvulnerable = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	FTimerHandle BiteInvulnerabilityTimer;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeBite();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndBiteInvulnerability();

	UFUNCTION(BlueprintCallable, Category = "Cat")
	void DropCarriedPrey();

	UFUNCTION(BlueprintPure, Category = "Cat")
	bool CanPickUpPrey() const { return !CarriedPrey && !bIsBiteInvulnerable; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
