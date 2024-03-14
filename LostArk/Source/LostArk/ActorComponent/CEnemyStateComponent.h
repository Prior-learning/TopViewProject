#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CEnemyStateComponent.generated.h"

UENUM()
enum class EStateEnemyType : uint8
{
    Idle = 0,     // �غ� ����
    Approach, // ����
    Strafe,   // �ɵ���
    Action,   // ���� ������
    Death,    // ���
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
// typedef float Statustype; // ���� ����
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

    void Add(const E_WHY_BLOCKED &reason);
    void Remove(const E_WHY_BLOCKED &reason);

  public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsIdleMode() const  {return mState == EStateEnemyType::Idle; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsApproachMode() const  {return mState == EStateEnemyType::Approach;}

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsStrafeMode() const  {return mState == EStateEnemyType::Strafe; }

    UFUNCTION(BlueprintPure) 
    FORCEINLINE bool IsActionMode() const  {return mState == EStateEnemyType::Action;}

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsDeathMode() const override {return mState == EStateEnemyType::Death;}

    virtual bool IsAimMode() const override {  return false; }

    void Take_Damage(float& DamageAmount);

    UFUNCTION(BlueprintCallable)
        void SetIdleMode();
    void SetApproachMode();
    void SetActionMode();
    void SetDeathMode();

    void SetMode(const EStateEnemyType &num, const E_WHY_BLOCKED& reason);
    bool FlagCheck(const E_WHY_BLOCKED &reason) const ;

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

    uint8 mFlagState = 0;

  private:
    float mHp = 0.f;
    float mCurrentCooltime = 3.f; //
    class AAIController *controller;


};
