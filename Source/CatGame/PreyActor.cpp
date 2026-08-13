// Fill out your copyright notice in the Description page of Project Settings.


#include "PreyActor.h"

#include "Components/SphereComponent.h"

// Sets default values
APreyActor::APreyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CatchSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CatchSpere"));
	SetRootComponent(CatchSphere);
	CatchSphere->InitSphereRadius(40.f);

	NoticeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("NoticeSphere"));
	NoticeSphere->SetupAttachment(CatchSphere);
	NoticeSphere->InitSphereRadius(400.f);
	NoticeSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CatchSphere);
}

// Called when the game starts or when spawned
void APreyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APreyActor::GetCaught()
{
	if (bIsCarried) return;

	bIsCarried = true;
	SetActorTickEnabled(false);

	if (CatchSphere) CatchSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (NoticeSphere) NoticeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Mesh) Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
