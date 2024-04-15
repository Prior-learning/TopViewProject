#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDamageText.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCDamageText : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDamageText();
protected:

	virtual void BeginPlay() override;
public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTextRenderComponent *mtextCmp;
};
