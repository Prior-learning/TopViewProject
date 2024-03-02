#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CPlayerStateComponent.generated.h"

//                    �ڵ� �ۼ��� == Dorong               //
//��Ʈ �÷��׸� ����� ���°����� �غ��� ���� ������ ���� �����Ͽ� �ۼ���.

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	UnArmed , Primary//....�߰�����
};

UENUM()
enum class E_State : uint16
{
	Idle,
	Attack,
	Run,
	Aim,
	Dash,
	Reload,
	Dead,
};

enum E_WHY_BLOCKED : uint64
{
	NONE = 0,
	ATTACKING = 1 << 1,
	RUNNING = 1 << 2,
	AIMING = 1 << 3,
	DASHING = 1 << 4,
	RELOADING = 1 << 5,
	DEAD = 1 << 6,
};

//enum class E_State : uint16;
//enum E_WHY_BLOCKED : uint64;

UCLASS()
class LOSTARK_API UCPlayerStateComponent : public UCStateComponent
{
	GENERATED_BODY()
public:
	UCPlayerStateComponent();

public:
	void Initialize();
	void Destroy();

public:
	void Add(const E_State& action, const E_WHY_BLOCKED& reason);
	void Remove(const E_State& action, const E_WHY_BLOCKED& reason);
	const bool IsContains(const E_State& action);
	void Clear(const E_State& action);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE E_WeaponType GetWeaponType() { return mWeaponType; }

	void SetUnarmed() { mWeaponType = E_WeaponType::UnArmed; }
	void SetPrimary() { mWeaponType = E_WeaponType::Primary; }
	
	void SetAiming() { bAiming = true; }
	void UnSetAiming() { bAiming = false; }
	bool IsAiming() { return bAiming; }

private:
	TMap<E_State, uint64> P_State;
	E_WeaponType mWeaponType;
	bool bAiming;
	
};

