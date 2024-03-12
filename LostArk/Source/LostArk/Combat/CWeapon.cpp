#include "CWeapon.h"
#include "GameFramework/Character.h"

ACWeapon *ACWeapon::CreateWeapon(UWorld *world, TSubclassOf<class ACWeapon> classof, ACharacter *owner)
{
    FActorSpawnParameters params;
    params.Owner = owner;

    ACWeapon *temp = world->SpawnActor<ACWeapon>(classof, params);

    temp->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
                            temp->mAttachBone);

    temp->mController = owner->GetController();

    return temp;
}

ACWeapon::ACWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

