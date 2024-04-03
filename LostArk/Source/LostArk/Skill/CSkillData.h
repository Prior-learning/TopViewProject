#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CSkillData.generated.h"

USTRUCT(BlueprintType)
struct FOnSkillData 
{
    GENERATED_BODY()

  public:

    UPROPERTY(EditAnywhere)
    class UAnimMontage *AnimMontage;

    UPROPERTY(EditAnywhere)
    float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
    FName StartSection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem *Effect;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform EffectTransform;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMoveFix;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAimFix;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float SkillCoolDown;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int LoopCount;

    float SkillTimer;
    bool bInCoolTime;
};

UCLASS()
class LOSTARK_API UCSkillData : public UDataAsset
{
	GENERATED_BODY()

  public:
    FORCEINLINE class ACOnSkill* GetOnSkill() { return OnSkill; }

  public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TSubclassOf<class ACOnSKill> OnSkillClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FOnSkillData> OnSkillDatas;

  public:
    void BeginPlay(class ACharacter *InOwnerCharacter);

  private:
    class ACOnSkill *OnSkill;
	
};
