#include "CHUD_Slot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
void UCHUD_Slot::BindButtonText(const FString& text)
{
    mButtonText->SetText(FText::FromString(text));
}

void UCHUD_Slot::BindCoolDownText(float time)
{
    mCoolTime = time;
    bCoolDown = true;
    FText FloatAsText = FText::FromString(FString::SanitizeFloat(mCoolTime));
    mCoolDownText->SetText(FloatAsText);
    SetCoolTextVisible();
}

void UCHUD_Slot::SetCoolTextVisible()
{
    mCoolDownText->SetVisibility(ESlateVisibility::Visible);
}

void UCHUD_Slot::SetCoolTextHidden()
{
    mCoolDownText->SetVisibility(ESlateVisibility::Hidden);
}

void UCHUD_Slot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    mSlotButton = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
    mButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonText")));
    mCoolDownText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolDownText")));
    mCoolTime = 0;
    bCoolDown = false;
    SetCoolTextHidden();
}

void UCHUD_Slot::NativeConstruct()
{

}

void UCHUD_Slot::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    if (bCoolDown)
    {
        mCoolTime -= InDeltaTime;
        if (mCoolTime<=0)
        {
            mCoolTime = 0;
            bCoolDown = false;
            SetCoolTextHidden();
        }
    }
}
