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
    FName mAttachBone;

  public:
    static ACGun *CreateWeapon(class UWorld *world, TSubclassOf<class ACWeapon> classof, class ACharacter *owner);
	
};
