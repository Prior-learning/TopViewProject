#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FHealthChanged);
DECLARE_MULTICAST_DELEGATE(FManaChanged);



USTRUCT(BlueprintType)
struct FPlayerStatus
{
    GENERATED_BODY()

  public:
    float MaxHealth;
    float MaxMana;
    float HealthPoint;
    float ManaPoint;
    bool bDead;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPlayerStatComponent();

public:
    void AddHP(float add);
    void MinusHP(float minus);
    void AddMP(float add);
    bool MinusMP(float minus);
 

    FHealthChanged OnHealthChanged;
    FManaChanged OnManaChanged;

public:
    float GetMaxHP(){return mStatus.MaxHealth;}
    float GetMaxMP(){return mStatus.MaxMana;}
    float GetHP(){return mStatus.HealthPoint;}
    float GetMP(){return mStatus.ManaPoint;}
    bool GetDead(){return mStatus.bDead;}

protected:
    FPlayerStatus mStatus;

	


		
};
