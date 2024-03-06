#include "CPNotifyEndRoll.h"
#include "../Global.h"
#include "../Attacker/CPlayer.h"

FString UCPNotifyEndRoll::GetNotifyName_Implementation() const
{
    return "Roll";
}

void UCPNotifyEndRoll::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACPlayer *player = Cast<ACPlayer>(MeshComp->GetOwner());
    CheckNull(player);

    player->EndRoll();
}
