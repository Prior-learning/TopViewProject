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

    FVector targetLoc = startLoc+(outDirection*700);  // Ÿ�� ����.
    float arcValue = 0.375f;                       // ArcParam (0.0-1.0)
    FVector outVelocity = FVector::ZeroVector;   // ��� Velocity
    if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
    {
        FPredictProjectilePathParams predictParams(20.0f, startLoc, outVelocity, 10.0f);   // 20: tracing ������ ������Ÿ�� ũ��, 15: �ù����̼ǵǴ� Max �ð�(��)
        predictParams.DrawDebugTime = 5.0f;     //����� ���� �������� �ð� (��)
        predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime �� �����ϸ� EDrawDebugTrace::Type::ForDuration �ʿ�.
        predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
        FPredictProjectilePathResult result;
        UGameplayStatics::PredictProjectilePath(this, predictParams, result);
        GMesh->AddImpulse(outVelocity); 

    }
}

