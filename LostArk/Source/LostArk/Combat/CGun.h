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
    class USkeletalMeshComponent *mesh;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACBullet> mBullet;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleHand;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleHolster;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem *FlashParticle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UParticleSystem *EjectParticle;




  public:
    static ACGun *CreateWeapon(class UWorld *world, TSubclassOf<class ACWeapon> classof, class ACharacter *owner);
   
    void Fire(ACharacter *owner);
    float GetFireRate(){return FireRate;}
    FName GetHandSocket(){return mRifleHand;}
    FName GetHolsterSocket(){return mRifleHolster;}


  private:
    float FireRate;
};
