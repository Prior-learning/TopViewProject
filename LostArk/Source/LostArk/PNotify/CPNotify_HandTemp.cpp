#include "CPNotify_HandTemp.h"
#include "../Attacker/CPlayer.h"
#include "../Global.h"

FString UCPNotify_HandTemp::GetNotifyName_Implementation() const
{
    return "HandTemp";
}

void UCPNotify_HandTemp::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACPlayer *player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(player);

    player->SetWeaponTemp();
}

