#include "CHUD_PlayerHealth.h"
#include "Components/ProgressBar.h"

#include "../ActorComponent/CPlayerStatComponent.h"
#include "GameFramework/Character.h"
#include "../Global.h"

void UCHUD_PlayerHealth::NativeOnInitialized()
{
    mHealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgress")));
    OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
    if (OwnerCharacter)
    {
        mStat = CHelpers::GetComponent<UCPlayerStatComponent>(OwnerCharacter);
    }
    if (mStat)
    {
        mStat->OnHealthChanged.AddUFunction(this, FName("SetHealthPersent"));
        //mStat->OnManaChanged.AddUFunction(this, FName("SetManaPersent"));
    }
}

void UCHUD_PlayerHealth::NativeConstruct()
{
    mHealthBar->SetPercent(1);

}

void UCHUD_PlayerHealth::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
}

void UCHUD_PlayerHealth::SetHealthPersent()
{
    float per = mStat->GetHP() / mStat->GetMaxHP();
    mHealthBar->SetPercent(per);
}
