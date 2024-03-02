#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COperationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCOperationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOperationComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	

};
