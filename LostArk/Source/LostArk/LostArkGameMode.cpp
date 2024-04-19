// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArkGameMode.h"
#include "LostArkPlayerController.h"
#include "LostArkCharacter.h"
#include "Widget/CHUD_SkillSlot.h"
#include "UObject/ConstructorHelpers.h"

ALostArkGameMode::ALostArkGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALostArkPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/AActor/Player/BP_CPlayer.BP_CPlayer_C'"));
    static ConstructorHelpers::FClassFinder<AHUD> LostArkHUD(TEXT("Blueprint'/Game/PUserInterface/BP_HUD.BP_HUD_C'"));
    static ConstructorHelpers::FClassFinder<UCHUD_SkillSlot> MainHUDAsset(TEXT("WidgetBlueprint'/Game/Widget/WB_SkillBar.WB_SkillBar_C'"));
   
    if (LostArkHUD.Succeeded())
        HUDClass = LostArkHUD.Class;

	if (PlayerPawnBPClass.Class != nullptr)
		DefaultPawnClass = PlayerPawnBPClass.Class;
	
    if (MainHUDAsset.Succeeded())
        HUDWidgetClass = MainHUDAsset.Class;
  
}

void ALostArkGameMode::BeginPlay()
{
    Super::BeginPlay();
    if (IsValid(HUDWidgetClass))
    {
        MainHUD = Cast<UCHUD_SkillSlot>(CreateWidget(GetWorld(), HUDWidgetClass));

        if (IsValid(MainHUD))
        {
            MainHUD->AddToViewport();
        }
    }
}
