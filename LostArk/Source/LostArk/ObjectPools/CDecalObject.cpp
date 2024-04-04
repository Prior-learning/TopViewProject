#include "CDecalObject.h"
#include "Components/DecalComponent.h"
#include "CParticleManager.h"
#include "../UParticlePooling.h"
#include "../Combat/ICombat.h"

#include "Kismet/GameplayStatics.h"

#include "Engine.h"
DEFINE_LOG_CATEGORY_STATIC(GameProject, Display, All)

//Sector 부채꼴임  나중에 수정
ACDecalObject::ACDecalObject()
{
   
}

void ACDecalObject::SetDecalInfo(FDecalInfo& info)
{
    mInfo = info;
    SetActorLocation(info.location);


    SetActorRotation(FQuat(info.direction));
    ShowDecal();
}
void ACDecalObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACDecalObject::SpawnParticle()
{
    ensureMsgf(mInfo.mImpact != nullptr, TEXT("Decal has not ParticleSystem"));
    if (!!mInfo.mImpact)
    {
        Fdir = GetActorForwardVector().GetSafeNormal2D();
        Rdir = GetActorRightVector().GetSafeNormal2D();

        switch (mInfo.shape)
        {
        case EDecalShape::Circle:
            CircleParticle();
            break;

        case EDecalShape::Triangle:
            AUParticlePooling *particle = ACParticleManager::Get().GetParticle();
            particle->SetActorLocation(GetActorLocation());
            particle->SetParticle(mInfo.mImpact);

            TriangleParticle(GetActorLocation(), 3);
            //particle->SetPower(mInfo.mDamage);
            break;
        }
       
    }
}

void ACDecalObject::CircleParticle()
{
    int AngleAxis = 0;
    float distance = 256.f * mInfo.circum; // 파티클의 중심이 원 살짝 안이여야 함.
    AUParticlePooling *particle;

    CheckDistanceAndTakeDamage();

    while(AngleAxis != 360)
    {
        AngleAxis += 10;
        FVector location = GetActorLocation();
        FVector RotateValue = location.RotateAngleAxis(AngleAxis, FVector(0, 0, 1)) + 1e-10;
        RotateValue = RotateValue.GetSafeNormal2D() * distance;
        
        location.X += RotateValue.X; 
        location.Y += RotateValue.Y;

        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorScale3D(mInfo.mParticleScale);
        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        //particle->SetPower(mInfo.mDamage);
        FString str = "";

        str.Append("RotateValue: ");
        str.Append(FString::SanitizeFloat(RotateValue.X, 2));
        str.Append(FString::SanitizeFloat(RotateValue.Y, 2));
        str.Append(FString::SanitizeFloat(RotateValue.Z, 2));

        str.Append("Particle location : ");
        str.Append(FString::SanitizeFloat(location.X, 2));
        str.Append(" , ");
        str.Append(FString::SanitizeFloat(location.Y, 2));

        UE_LOG(GameProject, Display, L"%s", *str);
    }
}

void ACDecalObject::TriangleParticle(FVector loc, int level)
{
    level--;
    if (level == 0)
        return;

    FVector location = loc;
    AUParticlePooling *particle;

    location += Fdir * 256.f / 2.f * mInfo.circum;
    // left
    {
        location += Rdir * 100.f;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        TriangleParticle(location, level);
    }
    //Right
    {
        location -= Rdir * 100.f * 2;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        TriangleParticle(location, level);
    }
   
}

void ACDecalObject::CheckDistanceAndTakeDamage()
{
    float distance, distance_MIN, distance_MAX;
    DistanceFromPlayer(distance);
    DistanceAttackRange(distance_MIN, distance_MAX);

    if (distance_MIN <= distance && distance <= distance_MAX)// 범위 안에 있다면
    {
        APlayerController *playercontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        IICombat *player = Cast<IICombat>(playercontroller->GetPawn());
        
        FDamageEvent type;
        player->Damaged(-mInfo.mDamage, type, nullptr, this, GetActorLocation(), nullptr);
        FString str = "AttackRange Chk Success \n";
        //UE_LOG(GameProject, Display, L"%s", *str);
    }
}

void ACDecalObject::DistanceFromPlayer(float &distance)
{
    APlayerController *playercontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    AActor *player = playercontroller->GetPawn();
    FString str;

    str = "";
    str.Append("Player Distance : ");
    distance = sqrt(pow((player->GetActorLocation().X - GetActorLocation().X), 2) +
               pow((player->GetActorLocation().Y - GetActorLocation().Y), 2)); 
    str.Append(FString::SanitizeFloat(distance, 2));
    //UE_LOG(GameProject, Display, L"%s", *str);
}

void ACDecalObject::DistanceAttackRange(float &distance_MIN, float &distance_MAX)
{
    distance_MIN = 256.f * mInfo.circum * mInfo.distancefromtcenter * 2;
    distance_MAX = 256.f * mInfo.circum;

    FString str = "";
    str.Append("Distance : ");
    str.Append(FString::SanitizeFloat(distance_MIN, 2));
    str.Append(" ~ ");
    str.Append(FString::SanitizeFloat(distance_MAX, 2));
    //UE_LOG(GameProject, Display, L"%s", *str);

}
