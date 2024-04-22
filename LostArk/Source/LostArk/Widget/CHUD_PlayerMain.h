#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_PlayerMain.generated.h"


UCLASS()
class LOSTARK_API UCHUD_PlayerMain : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UCHUD_SkillSlot *mSkillBar;
   /* UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UCHUD_Slot *PlayerHealth;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UCHUD_Slot *PlayerMana;*/

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
protected:
    UPROPERTY(BlueprintReadOnly)
    class UCPlayerStatComponent *mStat;

    UPROPERTY(BlueprintReadOnly)
    ACharacter *OwnerCharacter;
	
};
