#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_SkillSlot.generated.h"


UCLASS()
class LOSTARK_API UCHUD_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) 
    class UUserWidget *WB_Slot;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) 
    class UUserWidget *WB_Slot1;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) 
    class UUserWidget *WB_Slot2;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) 
    class UUserWidget *WB_Slot3;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) 
    class UUserWidget *WB_Slot4;

public:


protected:
  virtual void NativeOnInitialized();
  virtual void NativeConstruct() override;
  virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;


	
};
