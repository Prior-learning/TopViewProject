#include "CSkillData.h"
#include "COnSkill.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


void UCSkillData::BeginPlay(ACharacter *InOwnerCharacter)
{
    FTransform transform;

	//데이터 에셋을 안 만들어두고 추가해서 그런가 계속 오류터져서 주석쳐뒀음!
    if (!!OnSkillClass)
	{
		OnSkill = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACOnSkill>(OnSkillClass, transform, InOwnerCharacter);
		OnSkill->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
        OnSkill->SetActorLabel(GetLableName(InOwnerCharacter, "OnSkill"));
        OnSkill->SetDatas(OnSkillDatas);
        OnSkill->SetSlotData(SkillSlotData);
		UGameplayStatics::FinishSpawningActor(OnSkill, transform);
	}
}

FString UCSkillData::GetLableName(class ACharacter *InOwnerCharacter, FString InName)
{
    FString str;
    str.Append(InOwnerCharacter->GetActorLabel());
    str.Append("_");
    str.Append(InName);
    str.Append("_");
    str.Append(GetName().Replace(L"DA_", L""));

    return str;
}