#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPlayerStateComponent.h"

#include "CPlayerActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPlayerActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPlayerActionComponent();

protected:
  virtual void BeginPlay() override;

public:
	void SetUnarmed();
    void SetPrimary();
    void SetAim();
    void UnSetAim();
    void DoAttack();
    void DoRoll();
    void EndRoll();

public:
    UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsAimMode() { return mState->IsAimMode();}
    UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDeathMode() { return mState->IsDeathMode();}


private:
    UPROPERTY(VisibleDefaultsOnly)
    UCPlayerStateComponent * mState;

    E_WeaponType mPlayerWeaponType;


		
};
