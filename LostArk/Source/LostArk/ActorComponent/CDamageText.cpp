
#include "CDamageText.h"

UCDamageText::UCDamageText()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UCDamageText::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCDamageText::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

