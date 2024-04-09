#pragma once

#include "CoreMinimal.h"
#include "COnSkill.h"
#include "ISkillNotify.h"
#include "COnSkill_ShotGun.generated.h"


UCLASS()
class LOSTARK_API ACOnSkill_ShotGun : public ACOnSkill, public IISkillNotify
{
    GENERATED_BODY()

  public:

    virtual void OnSkill() override;
    virtual void Begin_OnSkill() override;
    virtual void End_OnSkill() override;

    virtual void SpawnMesh() override;
    virtual void OnTrigger() override;

   
  protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACGrenadeMesh> GrenadeClass;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleHand;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleTemp;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mHandThrow;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    float CoolTime;
    bool IsCoolDown;
    ACGrenadeMesh *mGrenade;
};
