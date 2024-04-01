#include "CPSkillComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"


UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	 if (bFSkillCool)
        mFSkillTimer -= DeltaTime;

	 if (bESkillCool)
         mESkillTimer -= DeltaTime;

	 if (mFSkillTimer <= 0)
     {
         bFSkillCool = false;
         mFSkillTimer = FSkillCoolDown;
     }
     if (mESkillTimer <= 0)
     {
         bESkillCool = false;
         mESkillTimer = ESkillCoolDown;
     }
}

void UCPSkillComponent::DoFSkill(ACharacter *Owner)
{
}

void UCPSkillComponent::DoESkill(ACharacter *Owner)
{
}

