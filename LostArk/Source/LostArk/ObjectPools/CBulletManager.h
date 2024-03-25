#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBulletManager.generated.h"

UCLASS()
class LOSTARK_API ACBulletManager : public AActor
{
    GENERATED_BODY()

  public:
    ACBulletManager();

    void Init();
    void Expand();
    void Return(class ACBullet *target);
    class ACBullet *Pop();
    static ACBulletManager &GetInstance();
    int32 GetPoolsize(){return Poolsize;}
  protected:
    virtual void BeginPlay() override;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACBullet> bulletClass;

  

  public:

  private:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    int32 mBulletPoolSize=30;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    int32 mExpandSize=10;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    int32 Poolsize = 0;

    TQueue<ACBullet*> BulletPool;
    static ACBulletManager *mInstance;

};
