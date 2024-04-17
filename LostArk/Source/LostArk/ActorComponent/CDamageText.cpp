#include "CDamageText.h"
#include "Components/TextRenderComponent.h"
#include "../Combat/CTextRenderComponent.h"

UCDamageText::UCDamageText()
{

    class UCTextRenderComponent *mtextCmp;

    for (int32 i = 0; i < mPoolTextSize; i++)
    {
        FString str = TEXT("Text");
        str.Append(FString::SanitizeFloat(i));
        mtextCmp = CreateDefaultSubobject<UCTextRenderComponent>(*str);
        mtextCmp->SetRelativeRotation({47, -175.f, 0});
        mtextCmp->SetVisibility(false);
        mtextCmp->SetTextRenderColor(FColor(204, 204, 0));
        
        mTextVec.Emplace(mtextCmp);
    }
}

void UCDamageText::BeginPlay()
{
	Super::BeginPlay();
  
}

void UCDamageText::TextRender(float damage,const FVector &location)
{

    static float mLoopSpeed = 0.7f;

    midx++;
    midx %= mPoolTextSize;

    mTextVec[midx]->SetWorldLocation(location);
    FVector forward = mTextVec[midx]->GetForwardVector().GetSafeNormal();

    FVector move_loc = location + forward * 150.f;

    mTextVec[midx]->SetRelativeLocation(move_loc);

    mTextVec[midx]->SetVisibility(true);
    
    mTextVec[midx]->SetText(FString::SanitizeFloat(damage,0));
    FTimerHandle temp;
    GetOwner()->GetWorldTimerManager().SetTimer(temp, mTextVec[midx], &UCTextRenderComponent::TextAutoOff, mLoopSpeed,
                                                false);
    

}
