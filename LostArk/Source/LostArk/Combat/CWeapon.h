// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class LOSTARK_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ACWeapon();
    virtual ~ACWeapon(){};

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
    static ACWeapon *CreateWeapon(class UWorld *world, TSubclassOf<class ACWeapon> classof, class ACharacter *owner);
    virtual void OnCollision(){};
	virtual void OffCollision(){};


  protected:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class USkeletalMeshComponent *mesh;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UParticleSystem * mHitParticle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "attach")
    FName mAttachBone; // 처음에 Attach 되는 Bone


    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Info")
    float mPower = 1.f;

    class AController *mController;


};
