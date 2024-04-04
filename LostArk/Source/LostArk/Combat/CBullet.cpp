#include "CBullet.h"

#include "../Global.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Character.h"
#include "../ObjectPools/CBulletManager.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "../Combat/ICombat.h"


ACBullet::ACBullet()
{
    CHelpers::CreateComponent(this, &StaticMesh, "Mesh");
    CHelpers::CreateComponent<UBoxComponent>(this, &mCollider, "Collider", StaticMesh);
    RootComponent = StaticMesh;
	Init();
}
ACBullet::~ACBullet()
{
    //CLog::Log("Destroy");
}
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
    mCollider->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnComponentBeginOverlap);
}

void ACBullet::Fire(const FVector &Direction,const float &returnrate)
{
    Projectile->Velocity = Direction * Projectile->InitialSpeed;
    Projectile->Activate(true);
    //CLog::Log("Activate");
    SetActorHiddenInGame(false);
    mCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetWorldTimerManager().SetTimer(ReturnHandle, this, &ACBullet::Deactivate, returnrate, false);
}

void ACBullet::SetPower(const float &damage)
{
    mdamage = damage;
    //CLog::Log("damage Setted");
}

void ACBullet::Init()
{
    Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    Projectile->SetUpdatedComponent(GetRootComponent());
    Projectile->InitialSpeed = 4000;
    Projectile->MaxSpeed = 4000;
    Projectile->bRotationFollowsVelocity = false;
    Projectile->bShouldBounce = false;
    Projectile->Deactivate();
    mCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorHiddenInGame(true);
    mdamage = 0;
}

void ACBullet::Deactivate()
{
    Projectile->Deactivate();
    SetActorHiddenInGame(true);
    ACBulletManager::GetInstance().Return(this);
    mCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //CLog::Print("Deactivate");
}

void ACBullet::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
    IICombat *hitedActor = Cast<IICombat>(OtherComp->GetOwner());
    CheckNull(hitedActor);
    CheckNull(mParticle);
    FDamageEvent mDamageEvent;
    hitedActor->Damaged(mdamage, mDamageEvent, nullptr, this, OverlappedComponent->GetComponentLocation(), mParticle);
}

