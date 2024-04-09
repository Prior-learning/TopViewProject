// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../ObjectPools/CDecalManager.h"
#include "CENotifyDecal.generated.h"

UCLASS()
class LOSTARK_API UCENotifyDecal : public UAnimNotify
{
    //리팩토링 할 때 모양별로 나눠서 구현하기.
    GENERATED_BODY()
  public:
    virtual FString GetNotifyName() const;
    virtual void Notify(class USkeletalMeshComponent *MeshComp, class UAnimSequenceBase *Animation);

  protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    FDecalInfo mInfo;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    EDecalDirection mDirection;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    FVector mOffset;


    
};
