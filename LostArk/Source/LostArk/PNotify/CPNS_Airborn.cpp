#include "CPNS_Airborn.h"
#include "../Global.h"
#include "../Attacker/CPlayer.h"
#include "CPNS_Airborn.h"

FString UCPNS_Airborn::GetNotifyName_Implementation() const
{
    return "AirBorn";
}

void UCPNS_Airborn::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACPlayer *player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(player);
    player->OnAirborn();
}

void UCPNS_Airborn::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACPlayer *player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(player);
    player->OffAirborn();
}
