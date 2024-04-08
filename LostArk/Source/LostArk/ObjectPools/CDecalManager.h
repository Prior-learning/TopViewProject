#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDecalManager.generated.h"



UENUM(BlueprintType)
enum class EDecalShape : uint8
{
    Circle,
    Rect,
    Triangle,
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

USTRUCT(BlueprintType)
struct FDecalInfo
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDecalShape shape;         
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem *mImpact;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector mParticleScale = FVector(1.f,1.f,1.f);   

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float degree;              // Circle Visible Degree
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float circum;              // Circle Size
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float distancefromtcenter; // distance from Center
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float mDamage;             // bool Particle Damage 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform trasformoffset;

    FVector location; // À§Ä¡
    FRotator direction;
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

    void SetDecalInfo(FDecalInfo& info);
  protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    int32 mPoolSize = 10;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACDecalObject> classof;

    static TQueue<class ACDecalObject *> mObjectpool;

    static ACDecalManager *Instance;
};
