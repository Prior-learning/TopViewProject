#include "CEnemy.h"
#include "../Global.h"
#include "Components/CapsuleComponent.h"
#include "../ActorComponent/CEnemyStateComponent.h"
#include "../ActorComponent/CEMontageComponent.h"

#include "../Combat/CMelee.h"
#include "../Combat/CWeapon.h"

ACEnemy::ACEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    InitInfo();
	CHelpers::CreateActorComponent<UCEnemyStateComponent>(this,&mState,"Statecddsdsomp");
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

}


void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ACEnemy::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                         AActor *DamageCauser)
{
    if (mState->IsDeathMode())
        return 0.f;
    mState->Take_Damage(DamageAmount);
    mMontageComp->PlayAnimMontage(EMontage_State::Hitted);

    
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