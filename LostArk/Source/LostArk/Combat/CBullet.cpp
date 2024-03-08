#include "CBullet.h"
#include "../Global.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACBullet::ACBullet()
{
    CHelpers::CreateComponent(this, &StaticMesh, "Mesh");
    RootComponent = StaticMesh;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    Projectile->SetUpdatedComponent(GetRootComponent());
    Projectile->InitialSpeed = 24000;
    Projectile->MaxSpeed = 24000;
    Projectile->bRotationFollowsVelocity = false;
    Projectile->bShouldBounce = false;
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBullet::Fire(const FVector &Direction)
{
    Projectile->Velocity = Direction * Projectile->InitialSpeed;
}


