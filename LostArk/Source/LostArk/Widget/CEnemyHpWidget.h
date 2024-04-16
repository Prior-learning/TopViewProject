#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CEnemyHpWidget.generated.h"


UCLASS()
class LOSTARK_API UCEnemyHpWidget : public UUserWidget
{
	GENERATED_BODY()
  public:
    
    static UCEnemyHpWidget* GetInstance()
    {
        return instance;
    }
    UFUNCTION(BlueprintImplementableEvent)
    void UpdateProgressBar(float percent);

    static UCEnemyHpWidget *instance;

};
