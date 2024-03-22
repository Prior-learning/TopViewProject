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

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
    mCollider->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnComponentBeginOverlap);
}

void ACBullet::TempCreate(UWorld *world, TSubclassOf<class ACBullet> classof, ACharacter *owner)
{
}

void ACBullet::Fire(const FVector &Direction)
{

    Projectile->Velocity = Direction * Projectile->InitialSpeed;
    CLog::Log("Activate");

    SetActorHiddenInGame(false);
    mCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    if (GetWorld()->GetTimerManager().IsTimerActive(ReturnHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(ReturnHandle);
    }
    GetWorld()->GetTimerManager().SetTimer(ReturnHandle, this, &ACBullet::Deactivate, 2.0f, true);
}



void ACBullet::Init()
{
    Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    Projectile->SetUpdatedComponent(GetRootComponent());
    Projectile->InitialSpeed = 10000;
    Projectile->MaxSpeed = 10000;
    Projectile->bRotationFollowsVelocity = false;
    Projectile->bShouldBounce = false;
}



void ACBullet::Deactivate()
{
    ACBulletManager::GetInstance().Return(this);
    SetActorHiddenInGame(true);
    mCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CLog::Log("Deactivate");
}

void ACBullet::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                       UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult &SweepResult)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
    IICombat *hitedActor = Cast<IICombat>(OtherComp->GetOwner());
    CheckNull(hitedActor);

    CheckNull(mParticle);
    FDamageEvent mDamageEvent;

    hitedActor->Damaged(mPower, mDamageEvent, nullptr, this, OverlappedComponent->GetComponentLocation(),
                        mParticle);


}

