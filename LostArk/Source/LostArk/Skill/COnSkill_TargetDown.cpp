#include "COnSkill_TargetDown.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"

void ACOnSkill_TargetDown::OnSkill()
{
    //�÷��̾��� ���¸� �ٲ۴�
    mState->SetWeaponType(E_WeaponType::Sniping);
	//�̵��Ұ�+��� ���ֻ̹���->�̹� ������Ʈ ������Ʈ�� ���ǵȵ�?
	 
	//���콺Ŀ���� ��ġ ����
	//���½�ų�� �Ѿ��.
}
void ACOnSkill_TargetDown::Begin_OnSkill()
{

}

void ACOnSkill_TargetDown::End_OnSkill()
{
}

void ACOnSkill_TargetDown::BeginPlay()
{
}

void ACOnSkill_TargetDown::Tick(float DeltaTime)
{
}
