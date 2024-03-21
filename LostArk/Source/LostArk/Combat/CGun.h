#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CGun.generated.h"

UCLASS()
class LOSTARK_API ACGun : public ACWeapon
{
	GENERATED_BODY()
  public:
    ACGun();
    virtual ~ACGun(){};

  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACBulletManager> mBulletPool;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleHand;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem *FlashParticle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UParticleSystem *EjectParticle;

  public:
    void Fire(ACharacter *owner);
    float GetFireRate(){return FireRate;}
    FName GetHandSocket(){return mRifleHand;}
    FName GetHolsterSocket(){return mAttachBone;}


  private:
    float FireRate;
};
