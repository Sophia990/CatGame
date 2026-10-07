#include "CatCharacter.h"
#include "Engine/World.h"

ACatCharacter::ACatCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Vitals = CreateDefaultSubobject<UVitalsComponent>(TEXT("Vitals"));
	Lives = MaxLives;
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACatCharacter::TakeBite()
{
	if (bIsBiteInvulnerable || Lives <= 0) return;

	Lives--;

	bIsBiteInvulnerable = true;
	GetWorldTimerManager().SetTimer(
		BiteInvulnerabilityTimer,
		this,
		&ACatCharacter::EndBiteInvulnerability,
		BiteInvulnerabilityDuration,
		false);
	
	DropCarriedPrey();

	if (Lives <= 0)
	{
		OnOutOfLives.Broadcast();
	}
}

void ACatCharacter::EndBiteInvulnerability()
{
	bIsBiteInvulnerable = false;
}

void ACatCharacter::DropCarriedPrey()
{
	if (!CarriedPrey) return;

	APreyActor* DroppedPrey = CarriedPrey;
	CarriedPrey = nullptr;

	DroppedPrey->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	DroppedPrey->SnapToGround(this);
	DroppedPrey->Release();
}