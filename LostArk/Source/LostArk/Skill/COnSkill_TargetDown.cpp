#include "COnSkill_TargetDown.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"

void ACOnSkill_TargetDown::OnSkill()
{
    //플레이어의 상태를 바꾼다
    mState->SetWeaponType(E_WeaponType::Sniping);
	//이동불가+상시 에이밍상태->이미 스테이트 컴포넌트에 정의된듯?
	 
	//마우스커서의 위치 추적
	//비긴온스킬로 넘어가기.
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
