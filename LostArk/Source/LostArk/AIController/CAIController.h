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

protected:

	UFUNCTION()
		void OnTargetDetected(class AActor* Actor, FAIStimulus Stimulus);

public:
	virtual FGenericTeamId GetGenericTeamId()const  override { return TeamID; }

	virtual void SetPerception();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	void RunAI();
	void StopAI();


protected:

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UAIPerceptionComponent* Perception;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBehaviorTree* mBehaviorTree;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBlackboardData* mBlackBoard;


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

	class UCEnemyStateComponent* mState;

	FGenericTeamId TeamID;

private:
	class ACEnemy* mOwner;
    class ACPlayer *target;

};
