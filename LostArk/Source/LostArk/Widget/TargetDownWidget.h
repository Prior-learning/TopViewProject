#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h" 
#include "TargetDownWidget.generated.h"


UCLASS()
class LOSTARK_API UTargetDownWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UTargetDownWidget(const FObjectInitializer &ObjectInitializer);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) // 배경 이미지
    class UImage *BackgroundImage;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) // 스코프 이미지
    class UImage *ScopeImage;

public:
    void FollowMousePos();
      
protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
};
