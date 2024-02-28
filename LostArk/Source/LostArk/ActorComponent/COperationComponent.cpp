#include "COperationComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"


UCOperationComponent::UCOperationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCOperationComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UCOperationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	return;
	CheckFalse(IsIdleMode());
	
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	CheckNull(owner);
	
	AController* controller = owner->GetController();


}


