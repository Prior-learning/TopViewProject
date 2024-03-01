#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CPlayerStateComponent.generated.h"

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

private:
	TMap<E_State, uint64> P_State;
	
};

