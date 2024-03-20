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
    void SetDecalInfo(EDecalShape &shape, FVector &location, float circum, float distancefromtcenter, float timer);

  protected:
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintImplementableEvent)
    void ShowDecal();
  
  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    EDecalShape mShape;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float mTimer;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float mCircum;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float mArea;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float mEraseArea;
};
