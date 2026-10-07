#include "PreyActor.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/MeshComponent.h"

APreyActor::APreyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CatchSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CatchSpere"));
	SetRootComponent(CatchSphere);
	CatchSphere->InitSphereRadius(40.f);

	NoticeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("NoticeSphere"));
	NoticeSphere->SetupAttachment(CatchSphere );
	NoticeSphere->InitSphereRadius(400.f);
	NoticeSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CatchSphere);
}

void APreyActor::BeginPlay()
{
	Super::BeginPlay();

	SnapToGround();
}

void APreyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APreyActor::GetCaught()
{
	if (bIsCarried) return;

	bIsCarried = true;
	SetActorTickEnabled(false);

	TArray<UPrimitiveComponent*> Primitives;
	GetComponents<UPrimitiveComponent>(Primitives);
	for (UPrimitiveComponent* Primitive : Primitives)
	{
		Primitive->SetSimulatePhysics(false);
		Primitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APreyActor::Release()
{
	if (!bIsCarried) return;

	bIsCarried = false;
	SetActorTickEnabled(true);

	TArray<UPrimitiveComponent*> Primitives;
	GetComponents<UPrimitiveComponent>(Primitives);
	for (UPrimitiveComponent* Primitive : Primitives)
	{
		if (UPrimitiveComponent* Archetype = Cast<UPrimitiveComponent>(Primitive->GetArchetype()))
		{
			Primitive->SetCollisionEnabled(Archetype->GetCollisionEnabled());
			Primitive->SetSimulatePhysics(Archetype->BodyInstance.bSimulatePhysics);
		}
	}
}

void APreyActor::SnapToGround(AActor* IgnoredActor)
{
	const FVector Location = GetActorLocation();
	const FVector Start = Location + FVector(0, 0, 50.f);
	const FVector End = Location - FVector(0, 0, GroundTraceDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (IgnoredActor)
	{
		Params.AddIgnoredActor(IgnoredActor);
	}

	FHitResult Hit;
	if (!GetWorld()->LineTraceSingleByChannel(Hit, Start, End,ECC_Visibility, Params)) return;

	FVector NewLocation = Location;
	NewLocation.Z = Hit.ImpactPoint.Z + GroundOffset;
	SetActorLocation(NewLocation);
}