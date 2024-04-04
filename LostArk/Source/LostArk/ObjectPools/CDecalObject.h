#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDecalManager.h"
#include "CDecalObject.generated.h"

UCLASS()
class LOSTARK_API ACDecalObject : public AActor
{
    GENERATED_BODY()

  public:
    ACDecalObject();
    void SetDecalInfo(FDecalInfo& info);
  protected:
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintImplementableEvent)
    void ShowDecal();

    UFUNCTION(BlueprintCallable)
    void SpawnParticle();

    void CircleParticle();
    void TriangleParticle(FVector loc, int level);

  private:
    void CheckDistanceAndTakeDamage();
    void DistanceFromPlayer(float& distance);
    void DistanceAttackRange(float &distance_MIN, float &distance_MAX);
  private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    FDecalInfo mInfo;

    FVector Fdir;
    FVector Rdir;
};
