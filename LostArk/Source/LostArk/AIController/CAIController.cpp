#include "CAIController.h"
#include "../Global.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

ACAIController::ACAIController()
{

	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "PerCeption");

	SetPerception();
}


ACAIController::~ACAIController()
{

}

//InitializeParentChain
void ACAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}


void ACAIController::SetPerception()
{
	CHelpers::CreatePerception<UAISenseConfig_Sight>(this, &SightConfig, "Sight Config");

	SetPerceptionComponent(*Perception);

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}



void ACAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	return;

	if (Stimulus.WasSuccessfullySensed())
	{
		//Blackboard->SetValueAsObject("TargetActor", Actor);

		//UKismetSystemLibrary::K2_ClearTimerHandle(this, target_handler);

		
	}
	else
		target_handler = UKismetSystemLibrary::K2_SetTimer(this, "Update_Target", 5.0f, false);
}

