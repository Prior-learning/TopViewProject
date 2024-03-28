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
    void SetDecalInfo(const EDecalShape &shape, const FRotator &direction, const float degree,
                      const  FVector &location,
                      const float circum, const float distancefromtcenter);
    void SetDecalInfo(FDecalInfo &info);
  protected:
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintImplementableEvent)
    void ShowDecal();
    UFUNCTION(BlueprintCallable)
    void SpawnParticle();

    void CircleParticle();
    void TriangleParticle(FVector loc, int level);
  private:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    EDecalShape mShape;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    FRotator mDirection;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    float mDegree;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    float mCircum;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    float mArea;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    float mEraseArea;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    class UParticleSystem *mParticle;


    FDecalInfo mInfo;

    FVector Fdir;
    FVector Rdir;
};
