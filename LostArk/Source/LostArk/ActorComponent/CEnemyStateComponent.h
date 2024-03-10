#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CEnemyStateComponent.generated.h"


UENUM(BlueprintType)
enum class EStateEnemyType : uint8
{
    Idle,     // �غ� ����
    Approach, // ����
    Strafe,   // �ɵ���
    Action,   // ���� ������
    Death,    // ���
    Max,
};
/*
   // == �ڵ� �ۼ��� :
   Arkchimy

         � ���¸� �˻��� ��  �������� �ø��� ���� �к��Ͽ� ����
        + EStateEnemyType �ڷ����� �ٸ� class�� ������Ű�� �ʵ��� �ϱ�����
        get set ����
          State���� �����Ͽ���.

    */
//typedef float Statustype; // ���� ����
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
    float mAttackRange = 120.f; // ��� ���� ��������� ������ �Ҳ���

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
    float mCooltime = 3.f; // ���� ��Ÿ��

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
