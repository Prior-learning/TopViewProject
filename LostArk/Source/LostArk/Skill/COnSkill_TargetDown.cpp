#include "COnSkill_TargetDown.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"
#include "../Combat/ICombat.h"

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
        ParticleComponent =UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect,Datas[0].EffectTransform, true);
        OnLineTrace(TraceHitResult.Location);
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

void ACOnSkill_TargetDown::BeginPlay()
{
    Super::BeginPlay();
    LeftShot = 0;
    CoolTime = 0;
    IsCoolDown = false;

}

void ACOnSkill_TargetDown::OnLineTrace(const FVector &startpos)
{
    FVector start = startpos;
    FVector end = FVector(start.X, start.Y, start.Z + 500);
    TArray<TEnumAsByte<EObjectTypeQuery>> queries;
    queries.Add(EObjectTypeQuery::ObjectTypeQuery3);
    TArray<AActor *> ignoreActors;
    ignoreActors.Add(OwnerCharacter);
    FHitResult hitResult;

    if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), start, end, 500, queries, false, ignoreActors,EDrawDebugTrace::ForOneFrame, hitResult, true))
    {
        IICombat *hitedActor = Cast<IICombat>(hitResult.GetActor());
        CheckNull(Datas[0].HittedEffect);
        CheckNull(hitedActor);
        FDamageEvent mDamageEvent;
        float DamageAmount = 10.f;
        if (!!hitedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("[TargetDown]Hitted Enemy"));
            // FRotator rotator = hitResult.ImpactNormal.Rotation();
            hitedActor->Damaged(DamageAmount, mDamageEvent, nullptr, this, hitResult.GetActor()->GetActorLocation(),Datas[0].HittedEffect);
            ignoreActors.Add(hitResult.GetActor());
        }
    }
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
