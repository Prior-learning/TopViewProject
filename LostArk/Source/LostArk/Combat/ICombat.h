// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ICombat.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTARK_API IICombat
{
	GENERATED_BODY()
public:
    virtual void CreateWeapon() = 0;

	virtual void OnCollision() = 0;
    virtual void OffCollision() = 0;
    virtual void Attack() = 0;

};
