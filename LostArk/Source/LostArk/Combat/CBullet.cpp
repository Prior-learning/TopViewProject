#include "CBullet.h"

#include "../Global.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Character.h"
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
    if (GetWorld()->GetTimerManager().IsTimerActive(ReturnHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(ReturnHandle);
    }
    // 타이머 시작
    GetWorld()->GetTimerManager().SetTimer(ReturnHandle, this, &ACBullet::TempDelete, 10.0f, false);
}

void ACBullet::TempDelete()
{
    Destroy();
}

void ACBullet::Init()
{
    Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    Projectile->SetUpdatedComponent(GetRootComponent());
    Projectile->InitialSpeed = 10000;
    Projectile->MaxSpeed = 10000;
    Projectile->bRotationFollowsVelocity = false;
    Projectile->bShouldBounce = false;
    Activate();
}

void ACBullet::Activate()
{
    mCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBullet::Deactivate()
{
    mCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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


    //TempDelete();
}

