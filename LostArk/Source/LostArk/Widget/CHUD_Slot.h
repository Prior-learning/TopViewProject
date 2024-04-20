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
    void UpdateCoolDownText(int a);


protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UButton *mSlotButton;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UTextBlock *mButtonText;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UTextBlock *mCoolDownText;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UProgressBar *mProgress;


  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  float mCoolTime;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  bool bCoolDown;


protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

	
};
