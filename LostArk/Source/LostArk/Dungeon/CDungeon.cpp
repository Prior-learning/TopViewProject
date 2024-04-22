#include "CDungeon.h"
#include "Components/BoxComponent.h"
#include "../Utilities/CLog.h"
#include "Kismet/KismetMathLibrary.h"

#include "../Attacker/CEnemy.h"
DEFINE_LOG_CATEGORY_STATIC(Dungeon, Error, All)

ACDungeon::ACDungeon()
{
	PrimaryActorTick.bCanEverTick = false;

	Init();
    LoadAsset();
    bNoBattle = false;
}


void ACDungeon::BeginPlay()
{
	Super::BeginPlay();
    mTrigger->SetRelativeLocation({575, 600, 0});
    SetState(bNoBattle ? EDungeonState::COMPLETE : EDungeonState::READY);
    for (auto trigger : mDoorTrigger)
    {
        trigger->SetHiddenInGame(false);
        
    }
    mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACDungeon::OnTriggerBeginOverlap);
    for (UBoxComponent *trigger : mDoorTrigger)
    {
        trigger->OnComponentBeginOverlap.AddDynamic(this, &ACDungeon::CreateRoom);
    }
    mDoorTrigger[2]->SetRelativeRotation({0, 0, 90});
    mDoorTrigger[3]->SetRelativeRotation({0, 0, 90});
}

void ACDungeon::Init()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

    mTrigger->SetBoxExtent({600, 600, 300});
    
    
    mTrigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
    mTrigger->SetupAttachment(RootComponent);

    static FName Sockets[] = { {TEXT("Left")},{TEXT("Right")},{TEXT("Up")},{TEXT("Down")} };

    for (const FName& Socket : Sockets)
    {
        
        UBoxComponent* temp = CreateDefaultSubobject<UBoxComponent>(Socket);
        temp->SetBoxExtent({150, 150, 100});
        temp->SetCollisionProfileName(TEXT("TriggerToPlayer"));
        temp->SetupAttachment(RootComponent, Socket);
        temp->ComponentTags.Add(Socket);
       
        mDoorTrigger.Add(temp);
    }

}

void ACDungeon::LoadAsset()
{
    FString AssetPath = TEXT("/Game/AActor/MapObject/Dungeon/Dungeon_Mesh.Dungeon_Mesh");
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Dungeon_Square(*AssetPath);
    if (Dungeon_Square.Succeeded())
        Mesh->SetStaticMesh(Dungeon_Square.Object);
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

    for (const FName& GateSocket : GateSockets)
    {
        UStaticMeshComponent *NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
        NewGate->SetStaticMesh(Door_mesh.Object);
        NewGate->SetupAttachment(RootComponent, GateSocket);
        
        mGateMesh.Add(NewGate);
    }
  
    
    FString enemiesPath = TEXT("/Game/AActor/Enemy/Goblin/Warrior/BP_CGoblin_Warrior.BP_CGoblin_Warrior_C");
    static ConstructorHelpers::FClassFinder<AActor> enemy_mesh(*enemiesPath);
    if(!enemy_mesh.Succeeded())
    {
        UE_LOG(Dungeon, Error, TEXT("Failed to load enmemymesh asset : %s"), *enemiesPath);
    }
    else
    {
        enemyClassof = enemy_mesh.Class;
    }
    
}

void ACDungeon::DeadEvent(ACEnemy *enemy)
{
    enemies.Remove(enemy);
    if (enemies.Num() == 0)
        SetState(EDungeonState::COMPLETE);
}

void ACDungeon::SetState(EDungeonState val)
{
    switch (val)
    {
        case (EDungeonState::BATTLE):
        {
            for (auto trigger : mDoorTrigger)
            {
                trigger->SetCollisionProfileName(TEXT("NoCollision"));
            }
            mTrigger->SetCollisionProfileName(TEXT("NoCollision"));
            OpenGate(false);
            break;
        }
        case (EDungeonState::READY): 
        {
            for (auto trigger : mDoorTrigger)
            {
                trigger->SetCollisionProfileName(TEXT("NoCollision"));
            }
            mTrigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
            OpenGate();
            break;
        }
        case (EDungeonState::COMPLETE): 
        {
            for (auto trigger : mDoorTrigger)
            {
                trigger->SetCollisionProfileName(TEXT("TriggerToPlayer"));
            }
            mTrigger->SetCollisionProfileName(TEXT("NoCollision"));
            OpenGate();
            break;
        }
    }
    mState = val;
}

void ACDungeon::OpenGate(bool bOpen)
{

    for (int i = 0; i < 8; i++)
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
    {
        CLog::Print("Called Battle Start");
        SetState(EDungeonState::BATTLE);
        FVector pivot_loc = FVector(GetActorLocation().X + 600.f, GetActorLocation().Y + 600.f, GetActorLocation().Z);


        for (int i = 0; i < 5; i++)
        {

            FVector2D Range = FMath::RandPointInCircle(500.f);
            FVector loc = pivot_loc + FVector(Range, 0.f);

            FRotator lookrot = UKismetMathLibrary::FindLookAtRotation(loc, pivot_loc);
            FActorSpawnParameters param;
            
            param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            ACEnemy *temp = GetWorld()->SpawnActor<ACEnemy>(enemyClassof, pivot_loc + FVector(Range, 50.f), lookrot, param);
            ensureMsgf(temp != nullptr, TEXT(" Enemy Spawn Fail"));
            temp->mDungeon = this;
            enemies.Add(temp);
        }
    }

    
}

void ACDungeon::CreateRoom(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                           int32 OtherBodylndex, bool bFromSweep, const FHitResult &SweepResult)
{
    
    TArray<FName> tags = OverlappedComponent->ComponentTags;

    FName SocketName = FName(tags[0].ToString().Left(1));
    CLog::Print(SocketName.ToString());
    if (!Mesh->DoesSocketExist(SocketName))
    {
        
        return;
    }
    FVector NewLocatlon = Mesh->GetSocketLocation(SocketName);
    CLog::Print(NewLocatlon);

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollistonQueryParam(NAME_None, false, this);
    FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
    bool bResult = GetWorld()->OverlapMultiByObjectType(OverlapResults, NewLocatlon, FQuat::Identity, ObjectQueryParam,
                                                        FCollisionShape::MakeSphere(500.f), CollistonQueryParam);
    if(!bResult)
    {
        auto NewSectlon = GetWorld()->SpawnActor<ACDungeon>(NewLocatlon, FRotator::ZeroRotator);
    }


}


