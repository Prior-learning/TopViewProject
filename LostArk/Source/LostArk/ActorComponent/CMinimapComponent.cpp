#include "CMinimapComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent.h"

UCMinimapComponent::UCMinimapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    mSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT ("Spring"));
    mCamera = CreateDefaultSubobject<USceneCaptureComponent>(TEXT ("Camera"));
   
    FRotator rot = {-90, 0, 0};
    mSpring->SetRelativeRotation(FQuat(rot));
    mSpring->TargetArmLength = 3000.f;
    
}


// Called when the game starts
void UCMinimapComponent::BeginPlay()
{
    mCamera->AttachToComponent(mSpring, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
    mCamera->SetHiddenInGame(false);
	Super::BeginPlay();

}


// Called every frame
void UCMinimapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

