#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UParticlePooling.generated.h"

UCLASS()
class LOSTARK_API AUParticlePooling : public AActor
{
	GENERATED_BODY()
	
public:	
	AUParticlePooling();
   virtual ~AUParticlePooling();
protected:
	virtual void BeginPlay() override;

public:
    void SetParticle(class UParticleSystem* InParticle);
   

	private:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    class UParticleSystemComponent *mParticle;

};
