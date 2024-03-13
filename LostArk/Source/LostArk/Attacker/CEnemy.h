#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Combat/ICombat.h"
#include "GenericTeamAgentInterface.h"
#include "CEnemy.generated.h"


UCLASS()
class LOSTARK_API ACEnemy : public ACharacter, public IICombat, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

  public:
    ACEnemy();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;


    virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                            AActor *DamageCauser) override;

    virtual FGenericTeamId GetGenericTeamId() const override
    {
        return mTeamID;
    }
  protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FVector> mPatrolPos;

  protected:
    UPROPERTY(VisibleDefaultsOnly)
    class UCEnemyStateComponent *mState;

    UPROPERTY(VisibleDefaultsOnly)
    class UCEMontageComponent *mMontageComp;


    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACWeapon> mWeaponClass;

    //UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class ACWeapon* mWeapon;

  public:
    virtual void CreateWeapon() override;
    virtual void OnCollision() override;
    virtual void OffCollision() override ;
    virtual void Attack() override;

    void InitInfo();

    FGenericTeamId mTeamID = 1;
};
