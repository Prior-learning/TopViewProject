// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LostArkGameMode.generated.h"

UCLASS(minimalapi)
class ALostArkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALostArkGameMode();

protected:
  virtual void BeginPlay() override;

protected:
  class UCHUD_SkillSlot *MainHUD;
  TSubclassOf<UUserWidget> HUDWidgetClass;

};

