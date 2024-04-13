#include "CMinimapComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent.h"

<<<<<<< HEAD

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
    mSpring->TargetArmLength = 3000.f;
}



void UCMinimapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector loc = GetOwner()->GetActorLocation();
    loc.Z = mSpring->GetRelativeLocation().Z;
    mSpring->SetRelativeLocation(loc);
    
}

=======
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

>>>>>>> Dorong
