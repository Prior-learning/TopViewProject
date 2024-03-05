#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CMelee.generated.h"

/**
 *
 */
UCLASS()
class LOSTARK_API ACMelee : public ACWeapon
{
    GENERATED_BODY()
  public:
    ACMelee();
    virtual ~ACMelee(){};

  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UStaticMeshComponent *mesh;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UBoxComponent *mCollider;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    FName mAttachBone;

  public:
    static ACMelee *CreateWeapon(class UWorld *world, TSubclassOf<class ACWeapon> classof, class ACharacter *owner);


   // virtual void BeginPlay(); override;

    virtual void OnCollision() override;
    virtual void OffCollision() override;


   private:
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult &SweepResult);

    UFUNCTION()
    void OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                               UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

   
};
