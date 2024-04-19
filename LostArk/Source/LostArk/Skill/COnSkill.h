#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSkillData.h"
#include "COnSkill.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSkillUsed); // 델리게이트 추가


UCLASS()
class LOSTARK_API ACOnSkill : public AActor
{
    GENERATED_BODY()
	
public:	
	ACOnSkill();

	FORCEINLINE void SetDatas(TArray<FOnSkillData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetSlotData(FSkillSlotData InData) { SlotData = InData; }

	FORCEINLINE TArray<FOnSkillData> GetDatas() { return Datas; }
    FORCEINLINE FSkillSlotData GetSlotData(){ return SlotData;}

	virtual void OnSkill() {}
	virtual void Begin_OnSkill() {}
    virtual void End_OnSkill(){OnSkillUsed.Broadcast();}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	FOnSkillUsed OnSkillUsed;

  protected:
    UPROPERTY(BlueprintReadOnly)
    class ACharacter *OwnerCharacter;

    UPROPERTY(BlueprintReadOnly)
    class UCPlayerStateComponent *mState;

    TArray<FOnSkillData> Datas;
    FSkillSlotData SlotData;

};
