#include "CEnemy.h"
#include "../Global.h"
#include "Components/CapsuleComponent.h"
#include "../ActorComponent/CEnemyStateComponent.h"
ACEnemy::ACEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetMesh()->SetRelativeLocation({ 0.f, 0.f, -90.f });
	GetMesh()->SetRelativeRotation(FRotator( 0.f,0.f,-90.f ));

	CHelpers::CreateActorComponent<UCEnemyStateComponent>(this,&mState,"StateComponent1");
}


void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	

}


void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

