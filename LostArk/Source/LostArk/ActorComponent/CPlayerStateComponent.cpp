#include "CPlayerStateComponent.h"


UCPlayerStateComponent::UCPlayerStateComponent() 
{

}

void UCPlayerStateComponent::Initialize()
{

}

void UCPlayerStateComponent::Destroy()
{
}

void UCPlayerStateComponent::Add(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		P_State.Emplace(action);
	//p_State�� Key���� action�� ���ٸ� �߰�. �߰��� �ൿ�� reason�� �ش��ϴ� ������ ������ �� ���� ���°� �Ǵ� ��.
	P_State[action] |= reason;
}

void UCPlayerStateComponent::Remove(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		return;
	//Add�Լ��� �߰��� action�� ����.
	P_State[action] &= ~reason;
}


const bool UCPlayerStateComponent::IsContains(const E_State& action)
{
	if (P_State.Contains(action) == false)
		return false;


	// �ش� ���¿� �ش��ϴ� ��Ʈ �÷��� �� �ϳ��� Ȱ��ȭ�Ǿ� �ִ��� Ȯ��. false��� �ش� �ൿ�� ����. �ƴ϶�� �ൿ�� �Ұ����ϵ���.
	uint64 StateFlag = P_State[action];
	return StateFlag != 0;
}

void UCPlayerStateComponent::Clear(const E_State& action)
{
	P_State.Remove(action);
}

