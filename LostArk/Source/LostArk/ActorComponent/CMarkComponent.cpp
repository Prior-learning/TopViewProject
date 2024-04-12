#include "CMarkComponent.h"
#include "PaperSpriteComponent.h"
UCMarkComponent::UCMarkComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

    mSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));

}

void UCMarkComponent::BeginPlay()
{
	Super::BeginPlay();
    USceneComponent *sprite = Cast<USceneComponent>(mSprite);
    if (!!sprite)
    {
        sprite->SetRelativeScale3D({5, 5, 5});
        sprite->SetRelativeRotation({0, 0, -90});
        sprite->SetRelativeLocation({1000, 0, 0});
    }
}


// Called every frame
void UCMarkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    USceneComponent *sprite = Cast<USceneComponent>(mSprite);
    if (!!sprite)
    {
        FVector loc = GetOwner()->GetActorLocation();
        loc.Z = 1000.f;
        sprite->SetRelativeLocation(loc);
    }
	
}

