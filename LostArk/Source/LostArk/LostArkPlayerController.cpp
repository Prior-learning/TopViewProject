#include "LostArkPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Attacker/CPlayer.h"
#include "Engine/World.h"

ALostArkPlayerController::ALostArkPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
    CurrentMouseCursor = EMouseCursor::Default;
}

void ALostArkPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
}

void ALostArkPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


    InputComponent->BindAxis("MoveForward", this, &ALostArkPlayerController::Move_Forward);
    InputComponent->BindAxis("MoveRight", this, &ALostArkPlayerController::Move_Right);

    /*InputComponent->BindAction("Equip1", EInputEvent::IE_Pressed, this, &ALostArkPlayerController::OnEquip1);
    InputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ALostArkPlayerController::OnAim);
    InputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ALostArkPlayerController::OffAim);
    InputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ALostArkPlayerController::BeginRoll);
    InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ALostArkPlayerController::BeginFire);
    InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ALostArkPlayerController::EndFire);*/


}
void ALostArkPlayerController::Move_Forward(float Axis)
{
    APawn *const player = GetPawn();
    if (player)
    {
        FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
        FVector direction = FQuat(rotator).GetForwardVector();
        player->AddMovementInput(direction, Axis);
    }
}

void ALostArkPlayerController::Move_Right(float Axis)
{
    APawn *const player = GetPawn();
    if (player)
    {
        FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
        FVector direction = FQuat(rotator).GetRightVector();
        player->AddMovementInput(direction, Axis);
    }
}

