#include "CPNotify_ReturnHand.h"
#include "../Global.h"
#include "../Attacker/CPlayer.h"

FString UCPNotify_ReturnHand::GetNotifyName_Implementation() const
{
    return "ReturnHand";
}

void UCPNotify_ReturnHand::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACPlayer *player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(player);

    player->SetWeaponHand();
}


