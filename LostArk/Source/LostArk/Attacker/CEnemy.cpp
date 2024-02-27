#include "CEnemy.h"
#include "../Utilities/CHelpers.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<UCapsuleComponent>(this, &capsule, "capsul", RootComponent);
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", capsule);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	capsule->InitCapsuleSize(42.f, 96.f);
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

