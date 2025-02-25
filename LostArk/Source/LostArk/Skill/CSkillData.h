#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CSkillData.generated.h"

UENUM(BlueprintType)
enum class ESkill_Type : uint8
{
    TargetDown,
    ShotGun,
    Ult,
    HealPotion,
    ManaPotion,
    Max
};

USTRUCT(BlueprintType)
struct FSkillSlotData
{

    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D *ItemIcon;
};


USTRUCT(BlueprintType)
struct FOnSkillData 
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    ESkill_Type Type;

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
    class UParticleSystem *HittedEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform HittedEffectTransform;

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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float SkillTimer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
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
    TSubclassOf<class ACOnSkill> OnSkillClass;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FSkillSlotData SkillSlotData;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FOnSkillData> OnSkillDatas;

  public:
    void BeginPlay(class ACharacter *InOwnerCharacter);

  private:
    FString GetLableName(class ACharacter *InOwnerCharacter, FString InName);
  private:
    class ACOnSkill *OnSkill;
	
};
