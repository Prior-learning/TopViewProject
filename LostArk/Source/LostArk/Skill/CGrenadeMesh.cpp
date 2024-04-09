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
}

void ACGrenadeMesh::Throwing()
{
    FVector startLoc = FVector::ZeroVector;      // �߻� ����
    FVector targetLoc = FVector(0, 1000, 1000);  // Ÿ�� ����.
    float arcValue = 0.5f;                       // ArcParam (0.0-1.0)
    FVector outVelocity = FVector::ZeroVector;   // ��� Velocity
    if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
    {
        FPredictProjectilePathParams predictParams(20.0f, startLoc, outVelocity, 15.0f);   // 20: tracing ������ ������Ÿ�� ũ��, 15: �ù����̼ǵǴ� Max �ð�(��)
        predictParams.DrawDebugTime = 15.0f;     //����� ���� �������� �ð� (��)
        predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime �� �����ϸ� EDrawDebugTrace::Type::ForDuration �ʿ�.
        predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
        FPredictProjectilePathResult result;
        UGameplayStatics::PredictProjectilePath(this, predictParams, result);
    }

}

