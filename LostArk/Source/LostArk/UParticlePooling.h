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
	virtual void Tick(float DeltaTime) override;
public:
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult &SweepResult);

    void SetParticle(class UParticleSystem* InParticle);
    void SetPower(float input){ mPower = input; }
    void OffBoxOverlap();
	private:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    class UParticleSystemComponent *mParticle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    class UBoxComponent *mBoxCollider;

	private:
    FTimerHandle ReturnHandle;
    float mPower = 0.f;
};
