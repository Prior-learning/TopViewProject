#include "CDamageText.h"
#include "Components/TextRenderComponent.h"

UCDamageText::UCDamageText()
{
	PrimaryComponentTick.bCanEverTick = true;
    mtextCmp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
}

void UCDamageText::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCDamageText::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector loc = GetOwner()->GetActorLocation();
    loc.Z = 200.f;

	
    mtextCmp->SetRelativeLocation(loc);
}

