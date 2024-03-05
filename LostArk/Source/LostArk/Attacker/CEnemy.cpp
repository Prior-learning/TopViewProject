#include "CEnemy.h"
#include "../Global.h"
#include "Components/CapsuleComponent.h"
#include "../ActorComponent/CEnemyStateComponent.h"
#include "../Combat/CMelee.h"
#include "../Combat/CWeapon.h"
ACEnemy::ACEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetMesh()->SetRelativeLocation({ 0.f, 0.f, -90.f });
	GetMesh()->SetRelativeRotation(FRotator( 0.f,0.f,-90.f ));

	CHelpers::CreateActorComponent<UCEnemyStateComponent>(this,&mState,"Statecddsdsomp");
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


void ACEnemy::CreateWeapon()
{
    CheckNull(mWeaponClass);

	mWeapon = ACMelee::CreateWeapon(GetWorld(), mWeaponClass, this);

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
