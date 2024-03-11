#include "CBullet.h"

#include "../Global.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACBullet::ACBullet()
{
    CHelpers::CreateComponent(this, &StaticMesh, "Mesh");
    CHelpers::CreateComponent<UBoxComponent>(this, &mCollider, "Collider", StaticMesh);

    RootComponent = StaticMesh;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    Projectile->SetUpdatedComponent(GetRootComponent());
    Projectile->InitialSpeed = 12000;
    Projectile->MaxSpeed = 12000;
    Projectile->bRotationFollowsVelocity = false;
    Projectile->bShouldBounce = false;
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
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

void ACBullet::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                       UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult &SweepResult)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
    ACharacter *hitedActor = Cast<ACharacter>(OtherComp->GetOwner());
    CheckNull(hitedActor);

    FDamageEvent mDamageEvent;
    CLog::Log(OverlappedComponent->GetFName().ToString());
    CLog::Log(OtherComp->GetFName().ToString());
    hitedActor->TakeDamage(mBulletDamage, mDamageEvent, mController, this);

    Destroy();
}
//메쉬 자체와 충돌할때 인듯?
void ACBullet::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                     FVector NormalImpulse, const FHitResult &Hit)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
    ACharacter *hitedActor = Cast<ACharacter>(OtherComp->GetOwner());
    CheckNull(hitedActor);

    Destroy();
}
 


