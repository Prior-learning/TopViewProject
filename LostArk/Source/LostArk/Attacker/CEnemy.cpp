#include "CEnemy.h"
#include "Components/CapsuleComponent.h"


ACEnemy::ACEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetMesh()->SetRelativeLocation({ 0.f, 0.f, -90.f });
	GetMesh()->SetRelativeRotation(FRotator( 0.f,0.f,-90.f ));
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

