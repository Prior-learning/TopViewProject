#include "CMinimapComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent.h"

UCMinimapComponent::UCMinimapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    Initialize();

}

void UCMinimapComponent::BeginPlay()
{
    mCamera->AttachToComponent(mSpring, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Super::BeginPlay();
   
}

void UCMinimapComponent::Initialize()
{
    mSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
    mCamera = CreateDefaultSubobject<USceneCaptureComponent>(TEXT("Camera"));
    
    mSpring->SetRelativeLocation({0, 0, 1000});
    FRotator rot = {-90, 0, 0};
    mSpring->SetRelativeRotation(FQuat(rot));
    mSpring->TargetArmLength = 4000.f;
}

void UCMinimapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector loc = GetOwner()->GetActorLocation();
    loc.Z = mSpring->GetRelativeLocation().Z;
    mSpring->SetRelativeLocation(loc);
    
}
<<<<<<< HEAD
=======

>>>>>>> Dorong
