#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_PlayerMana.generated.h"


UCLASS()
class LOSTARK_API UCHUD_PlayerMana : public UUserWidget
{
	GENERATED_BODY()
	
public:

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
