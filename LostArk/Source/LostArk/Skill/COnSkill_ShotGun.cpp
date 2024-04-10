#include "COnSkill_ShotGun.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "CGrenadeMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"

ACOnSkill_ShotGun::ACOnSkill_ShotGun()
{
    CHelpers::GetClass<ACGrenadeMesh>(&GrenadeClass, "Blueprint'/Game/AActor/Player/BP_Grenade.BP_Grenade_C'");
}

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

void ACOnSkill_ShotGun::SpawnMesh()
{
    CheckNull(GrenadeClass);//null bp를 만들었지만 스킬정보 가져올때 c클래스로 초기화를 해서 문제가 생긴듯
    UE_LOG(LogTemp, Warning, TEXT("[COnSkillShot::SpawnMesh_Notify]"));
    mGrenade = GetWorld()->SpawnActor<ACGrenadeMesh>(GrenadeClass);
    FVector throwlocation = OwnerCharacter->GetMesh()->GetSocketLocation(mHandThrow);
    if (mGrenade)
    { 
        mGrenade->SetOwner(OwnerCharacter);
        UE_LOG(LogTemp, Warning, TEXT("[COnSkillShot::SpawnSuccessed]"));
        mGrenade->SetActorLocation(throwlocation);
        mGrenade->Throwing();
    }
}

void ACOnSkill_ShotGun::OnTrigger()
{
    if (mGrenade)
    {
        Datas[0].EffectTransform.SetLocation(mGrenade->GetActorLocation());
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect, Datas[0].EffectTransform, true);
        mGrenade->Destroy();
    }
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
