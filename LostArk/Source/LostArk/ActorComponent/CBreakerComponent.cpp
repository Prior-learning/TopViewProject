#include "CBreakerComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "../Utilities/Defines.h"
#include "../Global.h"
UCBreakerComponent::UCBreakerComponent()
{
    //CHelpers::GetAsset<AActor>(&temp, "Blueprint'/Game/AActor/Enemy/Grux/BP_Breaker.BP_Breaker_C'");
    static ConstructorHelpers::FClassFinder<AActor> temp(TEXT("/Game/AActor/Enemy/Grux/BP_Breaker.BP_Breaker_C"));
    classof = temp.Class;
}


// Called when the game starts
void UCBreakerComponent::BeginPlay()
{
    Super::BeginPlay();
    mOwnerCharacter = Cast<ACharacter>(GetOwner());
    CheckNull(mOwnerCharacter);

    mOverlapActor = GetWorld()->SpawnActor<AActor>(classof);
    
    CheckNull(mOverlapActor);
    mOverlapActor->AttachToComponent(mOwnerCharacter->GetMesh(), 
        FAttachmentTransformRules(EAttachmentRule::KeepRelative, false),
                         "Break");
    mOverlapActor->SetOwner(GetOwner());
}

void UCBreakerComponent::OnBoxOverlap()
{
    ensureMsgf(mOverlapActor != nullptr, TEXT("mOverlapActor is empty"));
    if (!!mOverlapActor)
    {
        UBoxComponent *box = Cast<UBoxComponent>( mOverlapActor->GetComponentByClass(UBoxComponent::StaticClass()));
        box->SetGenerateOverlapEvents(true);
        //box->Activate();
    }
}

void UCBreakerComponent::OffBoxOverlap()
{
    ensureMsgf(mOverlapActor != nullptr, TEXT("mOverlapActor is empty"));
    if (!!mOverlapActor)
    {
        UBoxComponent *box = Cast<UBoxComponent>(mOverlapActor->GetComponentByClass(UBoxComponent::StaticClass()));
        box->SetGenerateOverlapEvents(false);
        //box->Deactivate();
    }
}


