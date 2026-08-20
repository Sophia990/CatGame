// Fill out your copyright notice in the Description page of Project Settings.


#include "DogAIController.h"
#include "CatCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TimerManager.h"
#include "NavigationSystem.h"

ADogAIController::ADogAIController()
{
	DogPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*DogPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1200.f;
	SightConfig->LoseSightRadius = 1600.f;
	SightConfig->PeripheralVisionAngleDegrees = 70.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	DogPerceptionComponent->ConfigureSense(*SightConfig);
	DogPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ADogAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviourTree)
	{
		RunBehaviorTree(BehaviourTree);
	}

	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		if (APawn* Dog = GetPawn())
		{
			BB->SetValueAsVector(TEXT("HomeLocation"), Dog->GetActorLocation());
		}
	}

	if (DogPerceptionComponent)
	{
		DogPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADogAIController::OnTargetPerceptionUpdated);
	}
}

void ADogAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB || !BB->GetValueAsObject(TEXT("TargetCat")))
	{
		GetWorldTimerManager().ClearTimer(PerchGiveUpTimerHandle);
		return;
	}
	if (CatIsUnreachable())
	{
		if (!GetWorldTimerManager().IsTimerActive(PerchGiveUpTimerHandle))
		{
			GetWorldTimerManager().SetTimer(
				PerchGiveUpTimerHandle,
				this,
				&ADogAIController::GiveUpChase,  // same ClearValue(TargetCat)
				PerchGiveUpDelay,
				false);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(PerchGiveUpTimerHandle);
	}
}

void ADogAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACatCharacter* Cat = Cast<ACatCharacter>(Actor);
	if (!Cat) return;

	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		GetWorldTimerManager().ClearTimer(GiveUpTimerHandle);
		BB->SetValueAsObject(TEXT("TargetCat"), Cat);
	} else
	{
		GetWorldTimerManager().SetTimer(
			GiveUpTimerHandle,
			this,
			&ADogAIController::GiveUpChase,
			GiveUpDelay,
			false);
	}
}

bool ADogAIController::CatIsUnreachable()
{
	const UBlackboardComponent* BB = GetBlackboardComponent();
	const AActor* Cat = BB ? Cast<AActor>(BB->GetValueAsObject(TEXT("TargetCat"))) : nullptr;
	if (!Cat) return false;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return false;

	FNavLocation Projected;
	const FVector Extent(50.f, 50.f, 200.f);
	return !NavSys->ProjectPointToNavigation(Cat->GetActorLocation(), Projected, Extent);
}

void ADogAIController::GiveUpChase()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->ClearValue(TEXT("TargetCat"));
	}
}