#pragma once

#include "CoreMinimal.h"
#include "../ActorComponent/CPlayerStateComponent.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"


UCLASS()
class LOSTARK_API UCAnimInstance : public UAnimInstance
{
    GENERATED_BODY()
  public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

  protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
    float Speed;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
    float Direction;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
    bool bAiming;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
    bool bDeath;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
    E_WeaponType AnimWeaponType;

  protected:
    class ACharacter *OwnerCharacter;
};
