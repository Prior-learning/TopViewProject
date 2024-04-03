#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CPSkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESkill : uint8
{
    TargetDown,
    Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPSkillComponent : public UActorComponent
{
	GENERATED_BODY()

private:

    /*UPROPERTY(EditDefaultsOnly)
    class UCSkillData *Datas[(int32)ESkill::Max];*/

public:
	/*UFUNCTION(BlueprintPure)
	FORCEINLINE class UCSkillData* GetCurrent() { return Datas[(int32)mSkill]; }*/

public:	
	UCPSkillComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
    void OnSkill();

 private:
    ESkill mSkill;
};
