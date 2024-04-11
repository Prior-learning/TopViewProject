#include "CGrenadeMesh.h"
#include "../Global.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACGrenadeMesh::ACGrenadeMesh()
{
    //CHelpers::CreateComponent(this, &GMesh, "GMesh");
    GMesh = this->CreateDefaultSubobject<UStaticMeshComponent>("GMesh");
    RootComponent = GMesh;
}

void ACGrenadeMesh::BeginPlay()
{
	Super::BeginPlay();
    GMesh->SetSimulatePhysics(true);
}

void ACGrenadeMesh::Throwing()
{
    //UE_LOG(LogTemp, Warning, TEXT("[CGrenade::Throw]"));
    CheckNull(GetOwner());

    FVector outDirection = GetOwner()->GetActorForwardVector();
    FVector startLoc = GetOwner()->GetActorLocation()+outDirection;

    FVector targetLoc = startLoc+(outDirection*700);  // 타겟 지점.
    float arcValue = 0.375f;                       // ArcParam (0.0-1.0)
    FVector outVelocity = FVector::ZeroVector;   // 결과 Velocity
    if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
    {
        FPredictProjectilePathParams predictParams(20.0f, startLoc, outVelocity, 10.0f);   // 20: tracing 보여질 프로젝타일 크기, 15: 시물레이션되는 Max 시간(초)
        predictParams.DrawDebugTime = 5.0f;     //디버그 라인 보여지는 시간 (초)
        predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime 을 지정하면 EDrawDebugTrace::Type::ForDuration 필요.
        predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
        FPredictProjectilePathResult result;
        UGameplayStatics::PredictProjectilePath(this, predictParams, result);
        GMesh->AddImpulse(outVelocity); 

    }
}

