#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CBullet.h"
#include "CGun.generated.h"

UENUM()
enum class E_Gun : uint16
{
    Rifle,
    ShotGun,
    Sniper
};

UCLASS()
class LOSTARK_API ACGun : public ACWeapon
{
	GENERATED_BODY()
  public:
    ACGun();
    virtual ~ACGun(){};

    virtual void Tick(float DeltaTime) override;

  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mRifleHand;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FireRate;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    E_Gun FireType;
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
   
};
