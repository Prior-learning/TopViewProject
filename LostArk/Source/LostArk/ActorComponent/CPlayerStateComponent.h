#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CPlayerStateComponent.generated.h"

//                    코드 작성자 == Dorong               //
//비트 플래그를 사용해 상태관리를 해보기 위해 예제를 보고 수정하여 작성함.

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	UnArmed , Primary
};

UENUM()
enum class E_State : uint16
{
	Idle,
	Equip,
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
	EQUIPING = 1 << 1,
	ATTACKING = 1 << 2,
	RUNNING = 1 << 3,
	AIMING = 1 << 4,
	DASHING = 1 << 5,
	RELOADING = 1 << 6,
	DEAD = 1 << 7,
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
	//EnemyComponent 를 만든 방식을 참고.
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmed() { return mWeaponType == E_WeaponType::UnArmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPrimary() { return mWeaponType == E_WeaponType::Primary; }

	void SetUnarmed() { mWeaponType = E_WeaponType::UnArmed; }
	void SetPrimary() { mWeaponType = E_WeaponType::Primary; }

private:
	TMap<E_State, uint64> P_State;
	E_WeaponType mWeaponType;
	
};

