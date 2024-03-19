#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticleManager.generated.h"

UCLASS()
class LOSTARK_API ACParticleManager : public AActor
{
    GENERATED_BODY()

  public:

    ACParticleManager();
    virtual ~ACParticleManager();

  protected:

    virtual void BeginPlay() override;

  public:

    virtual void Tick(float DeltaTime) override;

  public:
    static ACParticleManager &Get();
    class AUParticlePooling *GetParticle();
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPooling")
    int32 mPoolSize = 10;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPooling")
    TSubclassOf<class AUParticlePooling> classOfObject;

  private:
    TArray<class AUParticlePooling *> particlePool;
    static ACParticleManager *instance;
};
