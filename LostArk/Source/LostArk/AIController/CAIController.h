// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"


#include "CAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();
	~ACAIController();
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UAIPerceptionComponent* Perception;

protected:

	UFUNCTION()
		void OnTargetDetected(class AActor* Actor, FAIStimulus Stimulus);

public:
	virtual FGenericTeamId GetGenericTeamId()const  override { return TeamID; }

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetPerception();

protected:


	class UAISenseConfig_Sight* SightConfig;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Perception")
		float AISightRadius = 900.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Perception")
		float AILoseSightRadius = 50.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Perception")
		float AIFieldOfView = 45.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Perception")
		float AISightAge = 5.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Perception")
		float AILastSeenLocation = 1200.f;


	void Set_TeamId(int32 val) { TeamID = val; }

protected:
	FString Enemy_Type = "Melee";
	FTimerHandle target_handler;

	class UCStateComponent* State;
	class UOperation_Context* Context;


	FGenericTeamId TeamID;

};
