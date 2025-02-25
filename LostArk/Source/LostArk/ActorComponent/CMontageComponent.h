#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"


UENUM(BlueprintType)
enum class EMontage_State : uint8
{
    Attack = 0,
    Hitted,
    Roll,
    Skill,//Reload없애고 스킬로 대체
    Dead,
    Stun,
    AirBorne,
    Dash, // 돌진
    Skill2, // Enemy 는 특수 공격
    Max,
};
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    EMontage_State Type;

    UPROPERTY(EditAnywhere)
    class UAnimMontage *AnimMontage;

    UPROPERTY(EditAnywhere)
    float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
    FName StartSection;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    virtual void PlayAnimMontage(EMontage_State InState);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    UDataTable *DataTable;

   	FMontageData *Datas[(int16)EMontage_State::Max];
		
};
