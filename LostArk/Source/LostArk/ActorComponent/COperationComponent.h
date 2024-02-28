#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COperationComponent.generated.h"


// �ۼ��� arkchimy  
/*
	class ����  : Enemy �� ��� ���������� �����ϴ� class��
	���� ���  Patrol �߿��� �� �ʿ䰡 ������ �Ȱ�
	player�� �߰��ؼ� �پ�� �� �� �� �Լ��� ����ؼ� �ӵ��� �����Ѵ�.

	
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
	// ������� ������
	UPROPERTY(VisibleAnywhere)
		EOperationType type = EOperationType::Idle;

};
