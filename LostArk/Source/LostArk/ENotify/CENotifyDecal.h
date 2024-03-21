// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../ObjectPools/CDecalManager.h"
#include "CENotifyDecal.generated.h"

UCLASS()
class LOSTARK_API UCENotifyDecal : public UAnimNotify
{
    GENERATED_BODY()
  public:
    virtual FString GetNotifyName() const;
    virtual void Notify(class USkeletalMeshComponent *MeshComp, class UAnimSequenceBase *Animation);

  protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    EDecalShape mShape;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    EDecalDirection mDirection;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    float mDegree = 1.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    FVector mOffset;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    float mCenterDistance;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Decal")
    float mCircum = 1.f;

};
