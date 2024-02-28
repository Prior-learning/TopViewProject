#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COperationComponent.generated.h"


// 작성자 arkchimy  
/*
	class 설명  : Enemy 가 어떻게 움직일지를 결정하는 class임
	예로 들면  Patrol 중에는 뛸 필요가 없으니 걷고
	player를 발견해서 뛰어야 할 때 이 함수를 사용해서 속도를 변경한다.

	
*/
UENUM(BlueprintType)
enum class EOperationType : uint8
{
	Idle,Patrol,Chase,Around,Max,
};

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

	FORCEINLINE bool IsIdleMode() { return type == EOperationType::Idle; }

protected:
	// 디버깅이 쉽도록
	UPROPERTY(VisibleAnywhere)
		EOperationType type = EOperationType::Idle;

};
