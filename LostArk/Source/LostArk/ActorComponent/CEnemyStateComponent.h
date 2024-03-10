#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CEnemyStateComponent.generated.h"


UENUM(BlueprintType)
enum class EStateEnemyType : uint8
{
    Idle,     // 준비 상태
    Approach, // 접근
    Strafe,   // 맴돌기
    Action,   // 동작 실행중
    Death,    // 사망
    Max,
};
/*
   // == 코드 작성자 :
   Arkchimy

         어떤 상태를 검사할 지  직관성을 늘리기 위해 분별하여 만듬
        + EStateEnemyType 자료형을 다른 class에 참조시키지 않도록 하기위해
        get set 전부
          State별로 구현하였음.

    */
//typedef float Statustype; // 변경 용의
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

  public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsIdleMode()
    {
        return mState == EStateEnemyType::Idle;
    }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsApproachMode()
    {
        return mState == EStateEnemyType::Approach;
    }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsStrafeMode()
    {
        return mState == EStateEnemyType::Strafe;
    }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsActionMode()
    {
        return mState == EStateEnemyType::Action;
    }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsDeathMode()
    {
        return mState == EStateEnemyType::Death;
    }

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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    class UAnimMontage *AttackMontage;

  private:
    float mHp = 0.f;
    float mCurrentCooltime = 3.f;
};
