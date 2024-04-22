#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHUD_PlayerHealth.generated.h"


UCLASS()
class LOSTARK_API UCHUD_PlayerHealth : public UUserWidget
{
	GENERATED_BODY()
  
 
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class UProgressBar *mHealthBar;

public:
    UFUNCTION(BlueprintCallable)
    void SetHealthPersent();

  
protected:
    UPROPERTY(BlueprintReadOnly)
    class UCPlayerStatComponent *mStat;

    UPROPERTY(BlueprintReadOnly)
    ACharacter *OwnerCharacter;

	
};
