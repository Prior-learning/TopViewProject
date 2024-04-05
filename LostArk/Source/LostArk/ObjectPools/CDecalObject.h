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
    void SectorParticle(FVector loc, int level);

  private:
    void CheckDistanceAndTakeDamage(); // 피격 판정에 거리만 필요한 경우 ex) Circle
    void CheckDegreeAndDistanceTakeDmage(); // 각도도 필요한 경우 ex) Sector 

    void DistanceFromPlayer(float& distance);
    void DegreeFromPlayer(float &degree);
    void DistanceAttackRange(float &distance_MIN, float &distance_MAX);
  private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    FDecalInfo mInfo;

    FVector Fdir;
    FVector Rdir;
};
