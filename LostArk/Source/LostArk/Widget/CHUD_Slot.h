#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_Slot.generated.h"


UCLASS()
class LOSTARK_API UCHUD_Slot : public UUserWidget
{
	GENERATED_BODY()

public:

    void BindButtonText(const FString & text);
    void BindCoolDownText(float time);
    void SetCoolTextVisible();
    void SetCoolTextHidden();


protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UButton *mSlotButton;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UTextBlock *mButtonText;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UTextBlock *mCoolDownText;


protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

    float mCoolTime;
    bool bCoolDown;
	
};
