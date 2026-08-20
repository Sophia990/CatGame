// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DogAIController.generated.h"

/**
 * 
 */

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

UCLASS()
class CATGAME_API ADogAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADogAIController();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> DogPerceptionComponent;

protected:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	FTimerHandle GiveUpTimerHandle;
	FTimerHandle PerchGiveUpTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float GiveUpDelay = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float PerchGiveUpDelay = 2.5f;
	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	bool CatIsUnreachable();

	void GiveUpChase();
};
