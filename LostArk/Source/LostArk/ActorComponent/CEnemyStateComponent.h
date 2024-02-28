#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "CEnemyStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateEnemyType : uint8
{
	Idle , Action , Death, Max,
};


UCLASS()
class LOSTARK_API UCEnemyStateComponent : public UCStateComponent
{
	GENERATED_BODY()
	
public:
	UCEnemyStateComponent();
public:
	/* 
	//                                                         == �ڵ� �ۼ��� : Arkchimy

	// �������� �ø��� ���� + EStateEnemyType �ڷ����� �ٸ� class�� ���� ���ϵ����ϱ�����
	// State���� �����Ͽ���.
	// 
	 */
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return mState == EStateEnemyType::Idle; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return mState == EStateEnemyType::Action; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDeathMode() { return mState == EStateEnemyType::Death; }


	 void SetIdleMode() {  mState = EStateEnemyType::Idle; }

	 void SetActionMode() {  mState = EStateEnemyType::Action; }

	 void SetDeathMode() {  mState = EStateEnemyType::Death; }

private:
	EStateEnemyType mState;
};
