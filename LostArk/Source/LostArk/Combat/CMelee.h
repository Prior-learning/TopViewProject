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

  public:
 

    virtual void BeginPlay() override;

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

  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UBoxComponent *mCollider;

  private:
    TArray<class ACharacter *> OverlapActors;
    
};
