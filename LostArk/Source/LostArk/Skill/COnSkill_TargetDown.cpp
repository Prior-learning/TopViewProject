#include "COnSkill_TargetDown.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"

void ACOnSkill_TargetDown::OnSkill()
{
    CheckTrue(IsCoolDown);
    Super::OnSkill();

    if (LeftShot > 0 && mState->GetWeaponType() == E_WeaponType::Sniping)
    {
        Begin_OnSkill();
        return;
    }
    mState->SetWeaponType(E_WeaponType::Sniping);
    mState->SetSniping();
    LeftShot = Datas[0].LoopCount;
	//마우스커서의 위치 추적
	//비긴온스킬로 넘어가기.
}
void ACOnSkill_TargetDown::Begin_OnSkill()
{
    OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
    LeftShot--; 
    if (APlayerController *PC = Cast<APlayerController>(OwnerCharacter->GetController()))
    {
        FHitResult TraceHitResult;
        PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
        FVector Cursor_pos = TraceHitResult.Location;
        Datas[0].EffectTransform.SetLocation(TraceHitResult.Location);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect, Datas[0].EffectTransform, true);
    }

    if (LeftShot == 0)
        End_OnSkill();
}

void ACOnSkill_TargetDown::End_OnSkill()
{
    mState->SetWeaponType(E_WeaponType::Third);
    mState->UnSetSniping();
    CoolTime=Datas[0].SkillCoolDown;
    IsCoolDown = true;
}

void ACOnSkill_TargetDown::Trigger()
{
}

void ACOnSkill_TargetDown::BeginPlay()
{
    Super::BeginPlay();
    LeftShot = 0;
    CoolTime = 0;
    IsCoolDown = false;

}

void ACOnSkill_TargetDown::Tick(float DeltaTime)
{
    if (IsCoolDown)
    {
        CoolTime -= DeltaTime;
        if (CoolTime<=0)
        {
            CoolTime = 0;
            IsCoolDown = false;
        }
    }
}
