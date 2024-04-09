#include "COnSkill.h"

#include "../Global.h"
#include "../ActorComponent/CPlayerStateComponent.h"
#include "GameFramework/Character.h"

ACOnSkill::ACOnSkill()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACOnSkill::BeginPlay()
{
    OwnerCharacter = Cast<ACharacter>(GetOwner());
    mState = CHelpers::GetComponent<UCPlayerStateComponent>(OwnerCharacter);
	Super::BeginPlay();
}

void ACOnSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

