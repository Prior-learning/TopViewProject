#include "CHUD_Slot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UCHUD_Slot::BindButtonText(const FString &text)
{
    mButtonText->SetText(FText::FromString(text));
}

void UCHUD_Slot::BindCoolDownText(float time)
{
    mCoolTime = time;
    bCoolDown = true;
    UpdateCoolDownText((int)time);
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

void UCHUD_Slot::UpdateCoolDownText(int a)
{
    FText IntAsText = FText::FromString(FString::FromInt(a));
    mCoolDownText->SetText(IntAsText);
    if (a == 0)
        SetCoolTextHidden();

}

void UCHUD_Slot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    mSlotButton = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
    mButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonText")));
    mCoolDownText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolDownText")));
    mProgress = Cast<UProgressBar>(GetWidgetFromName(TEXT("CoolDownBar")));
    mCoolTime = 0;
    bCoolDown = false;
    SetCoolTextHidden();
}

void UCHUD_Slot::NativeConstruct()
{
}

void UCHUD_Slot::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);


}
