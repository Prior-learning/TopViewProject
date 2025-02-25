#include "LostArkPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Attacker/CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Global.h"

#include "Engine/World.h"

ALostArkPlayerController::ALostArkPlayerController()
{
    bEnemy = false;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
    CurrentMouseCursor = EMouseCursor::Default;
    bEnableMouseOverEvents = true;
     
}

void ALostArkPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
    //OnHovered();
    
}

void ALostArkPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    InputComponent->BindAxis("MoveForward", this, &ALostArkPlayerController::Move_Forward);
    InputComponent->BindAxis("MoveRight", this, &ALostArkPlayerController::Move_Right);
}
void ALostArkPlayerController::Move_Forward(float Axis)
{
    ACPlayer *const player = Cast<ACPlayer>(GetPawn());
    if (player && Cast<ACPlayer>(player)->IsCanMove())
    { 
        FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
        FVector direction = FQuat(rotator).GetForwardVector();
        player->AddMovementInput(direction, Axis);
    }
}

void ALostArkPlayerController::Move_Right(float Axis)
{
    ACPlayer *const player = Cast<ACPlayer>(GetPawn());
    if (player && player->IsCanMove())
    {
        FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
        FVector direction = FQuat(rotator).GetRightVector();
        player->AddMovementInput(direction, Axis);
    }
}

void ALostArkPlayerController::OnHovered()
{
    
}
void ALostArkPlayerController::UnHovered()
{
            // FVector direction = GetPawn()->GetActorForwardVector() * 2000.f;
            // FVector start = GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector();
            // FVector end = GetPawn()->GetActorLocation() + direction;

            // FCollisionQueryParams params;
            // params.AddIgnoredActor(GetOwner()); // 무시할 액터들.
            // FHitResult HitResult;               // 히트 결과 값 받을 변수.

            // bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end,
            // ECollisionChannel::ECC_Visibility, params); return bHit;
}

 
   
       
   