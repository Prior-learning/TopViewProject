#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCStateComponent::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
