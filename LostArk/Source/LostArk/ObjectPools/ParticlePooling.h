#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ParticlePooling.generated.h"

UCLASS()
class LOSTARK_API UParticlePooling : public UObject
{
	GENERATED_BODY()
  public:
    UParticlePooling();
    virtual ~UParticlePooling();

    static UParticlePooling &Get();
    class AUParticlePooling* GetParticle();
  private:
    TArray<class AUParticlePooling*> particlePool;
    
  /*private:
    UParticlePooling() = default;
    ~UParticlePooling();
    static UParticlePooling &Get();
    static void Create(UWorld *InWorld, int poolsize);

  public:
    static class AUParticlePooling *GetParticle();

  private:
    static TArray<class AUParticlePooling *> particlePool;*/
};
