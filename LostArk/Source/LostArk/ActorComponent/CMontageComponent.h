#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CPlayerStateComponent.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    E_State Type;

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

    void PlayRoll();

protected:
	virtual void BeginPlay() override;

private:
  void PlayAnimMontage(E_State InState);

private:
    
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    UDataTable *DataTable;

   	FMontageData *Datas[(int16)E_State::Max];


		
};
