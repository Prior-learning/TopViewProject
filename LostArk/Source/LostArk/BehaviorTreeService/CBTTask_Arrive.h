// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_Arrive.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UCBTTask_Arrive : public UBTTaskNode
{
	GENERATED_BODY()
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float mNearDistance = 60.f;
};
