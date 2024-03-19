#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LostArkPlayerController.generated.h"

UCLASS()
class ALostArkPlayerController : public APlayerController
{
    GENERATED_BODY()

  public:
    ALostArkPlayerController();

  protected:
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;

    UFUNCTION()
    void Move_Forward(float Axis);
    UFUNCTION()
    void Move_Right(float Axis);

  public:
    UFUNCTION()
    bool OnHovered();
    UFUNCTION()
    void UnHovered();
   
};


