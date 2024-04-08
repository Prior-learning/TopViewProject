#include "COnSkill_ShotGun.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"


void ACOnSkill_ShotGun::OnSkill()
{
    Super::OnSkill();

    CheckTrue(IsCoolDown);
    CheckFalse(mState->GetWeaponType() == E_WeaponType::Primary);

    if (Datas[0].bAimFix)
        mState->SetAim();

    if (Datas[0].bMoveFix)
        mState->SetCanMove(false);

    mState->SetSkill();
    OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);

}

void ACOnSkill_ShotGun::Begin_OnSkill()
{
    OwnerCharacter->PlayAnimMontage(Datas[1].AnimMontage, Datas[1].PlayRatio, Datas[1].StartSection);

}

void ACOnSkill_ShotGun::End_OnSkill()
{
    if (Datas[0].bAimFix)
        mState->UnSetAim();
    if (Datas[0].bMoveFix)
        mState->SetCanMove(true);

        mState->UnSetSkill();
}

void ACOnSkill_ShotGun::Trigger()
{

}

void ACOnSkill_ShotGun::BeginPlay()
{
    Super::BeginPlay();

    CoolTime = 0;
    IsCoolDown = false;
}

void ACOnSkill_ShotGun::Tick(float DeltaTime)
{
    if (IsCoolDown)
    {
        CoolTime -= DeltaTime;
        if (CoolTime <= 0)
        {
            CoolTime = 0;
            IsCoolDown = false;
        }
    }
}
