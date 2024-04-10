#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
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

    UPROPERTY(VisibleDefaultsOnly)
    FName mRifleTemp = "HandTemp";
        
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FireRate;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float ReturnRate;
   
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    E_Gun FireType;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem *FlashParticle;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UParticleSystem *EjectParticle;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class USoundCue *FireSoundCue;


  public:
    void Equip(ACharacter *owner);
    void UnEquip(ACharacter *owner);
    void Fire(ACharacter *owner);
    void SetHandTemp(ACharacter *owner);

    float GetFireRate(){return FireRate;}
    FName GetHandSocket(){return mRifleHand;}
    FName GetHolsterSocket(){return mAttachBone;}
    bool GetCoolDown(){return bCoolDown;}


  private:
     float mTimer;
     bool bCoolDown;
   
};
