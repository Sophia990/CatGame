// Fill out your copyright notice in the Description page of Project Settings.


#include "CatCharacter.h"

// Sets default values
ACatCharacter::ACatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Vitals = CreateDefaultSubobject<UVitalsComponent>(TEXT("Vitals"));
}

// Called when the game starts or when spawned
void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACatCharacter::TakeBite(AActor* AttackingDog)
{
	if (bIsBiteInvulnerable || Lives <= 0) return;

	Lives--;
	
	DropCarriedPrey();

	if (AttackingDog)
	{
		const FVector Away = (GetActorLocation() - AttackingDog->GetActorLocation()).GetSafeNormal();
		LaunchCharacter(Away * BiteLaunchSpeed + FVector(0.f, 0.f, 300.f), true, true);
	}

	bIsBiteInvulnerable = true;
	GetWorldTimerManager().SetTimer(
		BiteInvulnerabilityTimer,
		this,
		&ACatCharacter::EndBiteInvulnerability,
		BiteInvulnerabilityDuration,
		false);

	if (Lives <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of lives"));
	}
}

void ACatCharacter::EndBiteInvulnerability()
{
	bIsBiteInvulnerable = false;
}

void ACatCharacter::DropCarriedPrey()
{
	if (!CarriedPrey) return;

	CarriedPrey->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CarriedPrey = nullptr;
}