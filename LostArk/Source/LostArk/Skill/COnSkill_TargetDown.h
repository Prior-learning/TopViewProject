#pragma once

#include "CoreMinimal.h"
#include "COnSkill.h"
#include "COnSkill_TargetDown.generated.h"

UCLASS()
class LOSTARK_API ACOnSkill_TargetDown : public ACOnSkill
{
	GENERATED_BODY()

public:
	virtual void OnSkill() override;
    virtual void Begin_OnSkill() override;
    virtual void End_OnSkill() override;

    FORCEINLINE bool GetCoolTime(){return IsCoolDown;}

    FORCEINLINE bool GetIsCoolDown(){return IsCoolDown;}

protected:
   	virtual void BeginPlay() override;

    UFUNCTION()
    void OnLineTrace(const FVector &startpos);
  
public:	
	virtual void Tick(float DeltaTime) override;

  private:
    int LeftShot;
    float CoolTime;
    bool IsCoolDown;
    UParticleSystemComponent *ParticleComponent;
};
