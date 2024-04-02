#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CPSkillComponent.generated.h"

UENUM(BlueprintType)
enum class E_Skill : uint8
{
    Snipe,
    Max
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
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
    E_Skill Skill;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem *Effect;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ParticleScale;
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
    //UI추가예정?

    float SkillTimer;
    bool bInCoolTime;
};

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
 
    UFUNCTION(BlueprintCallable)
    virtual void DoSkill(E_Skill InSkill);
protected:
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    UDataTable *SkillDataTable;

    FSkillData *Datas[(int16)E_Skill::Max];
};
