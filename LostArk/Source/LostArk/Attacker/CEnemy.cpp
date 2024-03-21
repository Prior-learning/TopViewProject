#include "CEnemy.h"
#include "../Global.h"
#include "Components/CapsuleComponent.h"
#include "../ActorComponent/CEnemyStateComponent.h"
#include "../ActorComponent/CEMontageComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Combat/CMelee.h"
#include "../Combat/CWeapon.h"
#include "../UParticlePooling.h"
#include "../ObjectPools/CParticleManager.h"

ACEnemy::ACEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    InitInfo();
	CHelpers::CreateActorComponent<UCEnemyStateComponent>(this,&mStateComp,"Statecddsdcomp");
    CHelpers::CreateActorComponent<UCEMontageComponent>(this, &mMontageComp, "MontageComp");

}



void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
    CreateWeapon();
   
}


void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    CheckFalse(mStateComp->IsDeathMode());
    
}


void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACEnemy::Damaged(float Damage, FDamageEvent& Event, AController *controller, AActor *causer,const FVector hitLocation,
                      UParticleSystem *particle)
{
    TakeDamage(Damage, Event, controller, causer);
 
    
    AUParticlePooling *temp = ACParticleManager::Get().GetParticle();
    CheckNull(temp);
    if (particle == nullptr)
    {
        CLog::Log("particle is Nullptr");
        return;
    }
    temp->SetActorLocation(hitLocation);
    temp->SetParticle(particle);
}

float ACEnemy::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                         AActor *DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (mStateComp->IsDeathMode())
    {
        return 0.f;
    }

    mStateComp->Take_Damage(DamageAmount);
    if (mStateComp->IsDeathMode())
    {
        GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    if (!mStateComp->FlagCheck(ECurrentState::ATTACKINGSTATE) &&
        !mStateComp->FlagCheck(ECurrentState::DEATEH))
    {
        if(mMontageComp->GetKnockBack())
        {
            mMontageComp->PlayAnimMontage(EMontage_State::Hitted);
            mStateComp->SetMode(EStateEnemyType::Action, ECurrentState::HITTED);
        }
    }
	return 10.f;
}


void ACEnemy::CreateWeapon()
{
    CheckNull(mWeaponClass);

	mWeapon = ACWeapon::CreateWeapon(GetWorld(), mWeaponClass, this);

}

void ACEnemy::OnCollision()
{
    CheckNull(mWeapon);
    mWeapon->OnCollision();
}

void ACEnemy::OffCollision()
{
    CheckNull(mWeapon);
    mWeapon->OffCollision();
}

void ACEnemy::Attack()
{
    mMontageComp->PlayAnimMontage(EMontage_State::Attack);
}

void ACEnemy::InitInfo()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    GetMesh()->SetRelativeLocation({0.f, 0.f, -90.f});
    GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}