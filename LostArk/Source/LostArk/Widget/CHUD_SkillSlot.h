#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_SkillSlot.generated.h"


UCLASS()
class LOSTARK_API UCHUD_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
public:

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UCHUD_Slot *mSlot;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UCHUD_Slot *mSlot1;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UCHUD_Slot *mSlot2;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UCHUD_Slot *mSlot3;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UCHUD_Slot *mSlot4;
  
protected:
  virtual void NativeOnInitialized() override;
  virtual void NativeConstruct() override;
  virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

public:
  void UpdateSlotCoolTime(int a);

protected:

  UPROPERTY(BlueprintReadOnly)
  class UCPSkillComponent *mSkill;

  UPROPERTY(BlueprintReadOnly)
  ACharacter *OwnerCharacter;

  class ACOnSkill *FSkill;
  class ACOnSkill *ESkill;
	
};
