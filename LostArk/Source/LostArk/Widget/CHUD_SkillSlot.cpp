#include "CHUD_SkillSlot.h"
#include "CHUD_Slot.h"
#include "../Global.h"
#include "../ActorComponent/CPSkillComponent.h"
#include "../Skill/COnSkill.h"
#include "GameFramework/Character.h"


//UCHUD_SkillSlot::UCHUD_SkillSlot(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
//{
//
//}

void UCHUD_SkillSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    mSlot = Cast<UCHUD_Slot>(GetWidgetFromName(TEXT("WB_Slot")));
    mSlot1 = Cast<UCHUD_Slot>(GetWidgetFromName(TEXT("WB_Slot1")));
    mSlot2 = Cast<UCHUD_Slot>(GetWidgetFromName(TEXT("WB_Slot2")));
    mSlot3 = Cast<UCHUD_Slot>(GetWidgetFromName(TEXT("WB_Slot3")));
    mSlot4 = Cast<UCHUD_Slot>(GetWidgetFromName(TEXT("WB_Slot4")));

    mSlot->BindButtonText(TEXT("Q"));
    mSlot1->BindButtonText(TEXT("E"));
    mSlot2->BindButtonText(TEXT("F"));
    mSlot3->BindButtonText(TEXT("R"));
    mSlot4->BindButtonText(TEXT("T"));

    OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
    if (OwnerCharacter)
    {
        mSkill = CHelpers::GetComponent<UCPSkillComponent>(OwnerCharacter);
    }
    if (mSkill)
    {
        mSkill->SendSlotInfo.AddUFunction(this, FName("ShowCoolTime"));    
        mSkill->UpdateCoolTime.AddUFunction(this, FName("UpdateSlotCoolTime"));
    }
    
}

void UCHUD_SkillSlot::NativeConstruct()
{
    
}

void UCHUD_SkillSlot::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
   
}

void UCHUD_SkillSlot::ShowCoolTime(int a,int b)
{
    switch (a)
    {
    case 0:
        mSlot->BindCoolDownText(b);
        UE_LOG(LogTemp, Warning, TEXT("[SkillSlot::FSlotUpdate]"));
        break;
    case 1:
        mSlot1->BindCoolDownText(b);
        UE_LOG(LogTemp, Warning, TEXT("[SkillSlot::ESlotUpdate]"));
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;

    default:
        break;
    }
}

void UCHUD_SkillSlot::UpdateSlotCoolTime(int a, int b)
{
    switch (a)
    {
    case 0: 
        mSlot->UpdateCoolDownText(b);
        break;
    case 1: 
        mSlot1->UpdateCoolDownText(b);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;

        default:
        break;
    
    }
}
