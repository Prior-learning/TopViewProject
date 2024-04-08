#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Skill/CSkillData.h"
#include "CPSkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillButton : uint8
{
    F,E,
    Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPSkillComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	/*UPROPERTY(EditDefaultsOnly)
  class UCSkillData *Datas[(int32)ESkill_Type::Max];*/

public:	
	UCPSkillComponent();
  static void E_SkillBind();
  static void F_SkillBind();
  UCSkillData* GetData(int a) {return Datas[a];}
  

protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
    void OnSkill(ESkillButton InButton);
protected:
  UPROPERTY(EditDefaultsOnly)
  class UCSkillData *Datas[(int32)ESkill_Type::Max];

private:
  TMap<ESkillButton, ESkill_Type> SkillBind;

};
