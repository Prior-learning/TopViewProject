#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

/**
 *
 */
UCLASS()
class LOSTARK_API ACHUD : public AHUD
{
    GENERATED_BODY()
    friend class UCEnemyHpWidget;
  public:
    UFUNCTION(BlueprintCallable)
    void AddViewEnemyHpbar();

    UPROPERTY(BlueprintReadOnly)
    class UUserWidget *BossBar;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class UUserWidget> classof;
};
