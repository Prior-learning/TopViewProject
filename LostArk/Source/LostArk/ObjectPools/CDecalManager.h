#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDecalManager.generated.h"


UENUM(BlueprintType)
enum class EDecalShape : uint8
{
    Circle,
    Rect,
    Max,
};

UCLASS()
class LOSTARK_API ACDecalManager : public AActor
{
    GENERATED_BODY()

  private:
    ACDecalManager();

  public:
    static ACDecalManager *Get();
    void SetDecalInfo(EDecalShape &shape, FVector &location, float circum, float distancefromtcenter, float timer);

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    int mPoolSize = 10;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACDecalObject> classof;

    TQueue<class ACDecalObject *> mObjectpool;

    static ACDecalManager *Instance;
};
