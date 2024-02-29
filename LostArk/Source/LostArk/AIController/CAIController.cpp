#include "CAIController.h"
#include "../Global.h"
#include "../Attacker/CEnemy.h"
#include "../Attacker/CPlayer.h"

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

	CHelpers::GetAsset<UBehaviorTree>(&mBehaviorTree, TEXT("BehaviorTree'/Game/AActor/Enemy/Ai_Controller/BT_Chase.BT_Chase'"));
	CHelpers::GetAsset<UBlackboardData>(&mBlackBoard, TEXT("BlackboardData'/Game/AActor/Enemy/Ai_Controller/BB_Chase.BB_Chase'"));

	SetPerception();
}


ACAIController::~ACAIController()
{

}

//InitializeParentChain
void ACAIController::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ACEnemy>(GetPawn());
	CheckNull(mOwner);
}


void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void ACAIController::RunAI()
{
	if (UseBlackboard(mBlackBoard, Blackboard))
	{
		CLog::Print("RunAi");
		CheckNull(mBehaviorTree);
		RunBehaviorTree(mBehaviorTree);
	}
}

void ACAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
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
	
	if (Stimulus.WasSuccessfullySensed())
	{
		ACPlayer* target = Cast<ACPlayer>(Actor);
		CheckNull(target);

		CLog::Print("find player");
		Blackboard->SetValueAsObject("Target", Actor);
	}
	else
		Blackboard->SetValueAsObject("Target", nullptr);
}

