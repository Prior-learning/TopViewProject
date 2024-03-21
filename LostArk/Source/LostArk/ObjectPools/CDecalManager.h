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
UENUM(BlueprintType)
enum class EDecalDirection : uint8
{
    Forward,
    Right,
    Left,
    Back,
    Max,
};

UCLASS()
class LOSTARK_API ACDecalManager : public AActor
{
    GENERATED_BODY()

  private:
    ACDecalManager();
    ~ACDecalManager();
  public:
    static ACDecalManager *Get();
    void SetDecalInfo(const EDecalShape &shape, const FRotator &direction, const float degree,
                      const FVector &location, const float circum, const float distancefromtcenter);
  protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    int mPoolSize = 10;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACDecalObject> classof;

    static TQueue<class ACDecalObject *> mObjectpool;

    static ACDecalManager *Instance;
};
