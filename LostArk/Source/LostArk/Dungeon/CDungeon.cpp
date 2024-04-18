#include "CDungeon.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Dungeon, Error, All)

ACDungeon::ACDungeon()
{
	PrimaryActorTick.bCanEverTick = false;

	Init();
    LoadAsset();
    bNoBattle = false;

    mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACDungeon::OnTriggerBeginOverlap);
}


void ACDungeon::BeginPlay()
{
	Super::BeginPlay();
    SetState(bNoBattle ? EDungeonState::COMPLETE : EDungeonState::READY);
}

void ACDungeon::Init()
{
    mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = mMesh;

    // Center Trigger 
    mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));


    mTrigger->SetBoxExtent({650, 650, 300});
    
    //mTrigger->SetupAttachment(RootComponent);
    mTrigger->SetRelativeLocation({600, 650, 0});
    mTrigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
}

void ACDungeon::LoadAsset()
{
    FString AssetPath = TEXT("/Game/AActor/MapObject/Dungeon/Dungeon_Mesh.Dungeon_Mesh");
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Dungeon_Square(*AssetPath);
    if (Dungeon_Square.Succeeded())
        mMesh->SetStaticMesh(Dungeon_Square.Object);
    else
    {
        UE_LOG(Dungeon, Error, TEXT("Failed to load staticmesh asset : %s"), *AssetPath);
    }

    FString GateAssetPath = TEXT("/Game/InfinityBladeGrassLands/Environments/Misc/Exo_Deco02/StaticMesh/"
                                 "SM_Exo_Decos_Door01.SM_Exo_Decos_Door01");
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Door_mesh(*GateAssetPath);
    if (!Door_mesh.Succeeded())
    {
        UE_LOG(Dungeon, Error, TEXT("Failed to load staticmesh asset : %s"), *GateAssetPath);
    }
    static FName GateSockets[] = {{TEXT("R_Door0")}, {TEXT("R_Door1")}, {TEXT("L_Door0")}, {TEXT("L_Door1")},
                                  {TEXT("U_Door0")}, {TEXT("U_Door1")}, {TEXT("D_Door0")}, {TEXT("D_Door1")}};

    for (FName GateSocket : GateSockets)
    {
        UStaticMeshComponent *NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
        NewGate->SetStaticMesh(Door_mesh.Object);
        NewGate->SetupAttachment(RootComponent, GateSocket);
        mGateMesh.Add(NewGate);
    }
}

void ACDungeon::SetState(EDungeonState val)
{
    switch (val)
    {
        case (EDungeonState::BATTLE):
        {
            mTrigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
            break;
        }
        case (EDungeonState::READY): {
            mTrigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
            OpenGate(false);
            break;
        }
        case (EDungeonState::COMPLETE): 
        {
            mTrigger->SetCollisionProfileName(TEXT("NoCollision"));
            OpenGate();
            break;
        }
    }
    mState = val;
}

void ACDungeon::OpenGate(bool bOpen)
{
    for (int i =0; i < 8; i++)
    {
        if (i % 2 == 0)
            mGateMesh[i]->SetRelativeRotation(bOpen ? FRotator(0, 90, 0) : FRotator::ZeroRotator);
        else
            mGateMesh[i]->SetRelativeRotation(bOpen ? FRotator(0, -90, 0) : FRotator::ZeroRotator);
    }

}

void ACDungeon::OnTriggerBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodylndex, bool bFromSweep,
                                      const FHitResult &SweepResult)
{
    if (mState == EDungeonState::READY)
        SetState(EDungeonState::BATTLE);
}


