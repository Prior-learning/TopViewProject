#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSkillData.h"
#include "COnSkill.generated.h"

UCLASS()
class LOSTARK_API ACOnSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	ACOnSkill();

	//FORCEINLINE void SetDatas(TArray<FOnSkillData> InDatas) { Datas = InDatas; }

	virtual void OnSkill() {}
	virtual void Begin_OnSkill() {}
	virtual void End_OnSkill() {}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(BlueprintReadOnly)
    class ACharacter *OwnerCharacter;

    UPROPERTY(BlueprintReadOnly)
    class UCPlayerStateComponent *mState;

   // TArray<FOnSkillData> Datas;

};
