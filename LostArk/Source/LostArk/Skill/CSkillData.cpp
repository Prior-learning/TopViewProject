#include "CSkillData.h"
#include "COnSkill.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


void UCSkillData::BeginPlay(ACharacter *InOwnerCharacter)
{
    FTransform transform;
	//������ ������ �� �����ΰ� �߰��ؼ� �׷��� ��� ���������� �ּ��ĵ���!
    /*if (!!OnSkillClass)
	{
		OnSkill = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACOnSkill>(OnSkillClass, transform, InOwnerCharacter);
		OnSkill->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
        OnSkill->SetDatas(OnSkillDatas);
		UGameplayStatics::FinishSpawningActor(OnSkill, transform);
	}*/
}
