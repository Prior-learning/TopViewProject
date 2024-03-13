#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CEnemyStateComponent.generated.h"

UENUM()
enum class EStateEnemyType : uint8
{
    Idle,     // 준비 상태
    Approach, // 접근
    Strafe,   // 맴돌기
    Action,   // 동작 실행중
    Death,    // 사망
    Max,
};
enum E_WHY_BLOCKED : uint8
{
    NONE = 0,
    ATTACKING = 1 << 1,
    HITTED = 1 << 2,
    MOVE = 1 << 3,
    DEATEH = 1 << 4,
};
// typedef float Statustype; // 변경 용의
UCLASS()
class LOSTARK_API UCEnemyStateComponent : public UCStateComponent
{
    GENERATED_BODY()

  public:
    UCEnemyStateComponent();
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;
    void OperationSelect(const AActor *target);


    void Add(const EStateEnemyType &action, const E_WHY_BLOCKED &reason);
    void Remove(const EStateEnemyType &action, const E_WHY_BLOCKED &reason);
    const bool IsContains(const EStateEnemyType &action);
    void Clear(const EStateEnemyType &action);

  public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsIdleMode() const{return mState == EStateEnemyType::Idle; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsApproachMode() const{return mState == EStateEnemyType::Approach;}

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsStrafeMode() const{return mState == EStateEnemyType::Strafe; }

    UFUNCTION(BlueprintPure) 
    FORCEINLINE bool IsActionMode() const{return mState == EStateEnemyType::Action;}

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsDeathMode() const{return mState == EStateEnemyType::Death;}

    virtual bool IsAimMode() const{ return false; }

    void Take_Damage(float DamageAmount);

    void SetIdleMode();
    void SetApproachMode();
    void SetStrafeMode();
    void SetActionMode();
    void SetDeathMode();

    void SetMode(BYTE num);

  protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
    float mAttackRange = 120.f; // 어느 정도 가까워져야 공격을 할껀지

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
    float mCooltime = 3.f; // 공격 쿨타임

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Status")
    float MaxHp = 3.f;

  protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    EStateEnemyType mState;

    TMap<EStateEnemyType, uint8> mP_State; // 멀티스레드 환경에서 되도록 Mutex lock 
  private:
    float mHp = 0.f;
    float mCurrentCooltime = 3.f; //
    class AAIController *controller;


};
