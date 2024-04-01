#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FSkillCoolDown;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int FSkillLeft;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float ESkillCoolDown;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem *FSkillParticle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem *ESkillParticle;

	bool GetFSkillCool(){return bFSkillCool;}
   	bool GetESkillCool(){return bESkillCool;}
    int GetFLeft(){return FSkillLeft;}

  public:
    void DoFSkill(ACharacter *Owner);
    void DoESkill(ACharacter *Owner);


  private:
    bool bFSkillCool;
    bool bESkillCool;
    float mFSkillTimer;
    float mESkillTimer;
};
