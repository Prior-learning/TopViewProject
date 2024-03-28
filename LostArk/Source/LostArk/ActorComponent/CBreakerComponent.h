
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBreakerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCBreakerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBreakerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void OnBoxOverlap();
	void OffBoxOverlap();

private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<class AActor> classof;

	UPROPERTY(meta = (AllowPrivateAccess = true))
	class ACharacter *mOwnerCharacter;
    UPROPERTY(meta = (AllowPrivateAccess = true))
    class AActor * mOverlapActor;
};
