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
	//                                                         == 코드 작성자 : Arkchimy

	// 직관성을 늘리기 위해 + EStateEnemyType 자료형을 다른 class에 참조 안하도록하기위해
	// State별로 구현하였음.
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
