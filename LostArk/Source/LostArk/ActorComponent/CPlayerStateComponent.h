#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CPlayerStateComponent.generated.h"

//                    �ڵ� �ۼ��� == Dorong               //
//��Ʈ �÷��׸� ����� ���°����� �غ��� ���� ������ ���� �����Ͽ� �ۼ���.



UENUM()
enum class E_State : uint16
{
	Attack,
	Airborn,
	Aim,
	Roll,
	Reload,
	Skill,
	Snipe,
	Dead,
	Max
};

enum E_WHY_BLOCKED : uint64
{
    NONE = 0,
    ATTACKING = 1 << 1,
    AirBorned = 1 << 2,
    AIMING = 1 << 3,
    ROLLING = 1 << 4,
    RELOADING = 1 << 5,
    SKILLUSE = 1 << 6,
    SNIPING = 1 << 7,
	DEAD = 1 << 8
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

	void SetWeaponType(E_WeaponType InType){mWeaponType=InType;}
	bool IsFireMode(){return bFiring;}
    bool IsCanMove(){return bCanMove;}
	virtual bool IsAimMode() const override {return bAiming;}
    virtual bool IsDeathMode() const override {return 0;}

public:
    void SetRoll();
    void UnSetRoll();
    void SetAim();
    void UnSetAim();
    void SetFire();
    void UnSetFire();
    void SetAirborn();
    void UnSetAirborn();
    void SetReload();
    void UnSetReload();
    void SetSkill();
    void UnSetSkill();
    void SetSniping();
    void UnSetSniping();


 
private:
	TMap<E_State, uint64> P_State;// ��Ƽ������ ȯ�濡�� �ǵ��� Mutex lock 

	bool bCanMove;
	bool bAiming;
    bool bFiring;
	
};

