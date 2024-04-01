// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
    Primary, 
    Secondary,
    Third,
    Skill,
    Sniping
};

UCLASS(Abstract)
class LOSTARK_API UCStateComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UCStateComponent();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

  public: 
    virtual bool IsAimMode() const PURE_VIRTUAL(UCStateComponent::IsAimMode(), return false;);
    virtual bool IsDeathMode() const PURE_VIRTUAL(UCStateComponent::IsDeathMode(), return false;);

    E_WeaponType GetWeaponType(){return mWeaponType;}
  protected:
    E_WeaponType mWeaponType;
};
