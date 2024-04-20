#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDungeon.generated.h"

UENUM()
enum class EDungeonState : uint8
{
    READY = 0,
	BATTLE,
	COMPLETE
 };


UCLASS()
class LOSTARK_API ACDungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACDungeon();

protected:
	virtual void BeginPlay() override;
	void Init();
    void LoadAsset();

  private:
    void SetState(EDungeonState val);
    void OpenGate(bool bOpen = true);

	UFUNCTION()
    void OnTriggerBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                               UPrimitiveComponent *OtherComp, int32 OtherBodylndex, bool bFromSweep,
                               const FHitResult &SweepResult);
    UFUNCTION()
    void CreateRoom(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                               UPrimitiveComponent *OtherComp, int32 OtherBodylndex, bool bFromSweep,
                               const FHitResult &SweepResult);
  private:

    UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
    TArray<UStaticMeshComponent *> mGateMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
    class UBoxComponent* mTrigger;

    UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
    TArray<class UBoxComponent *> mDoorTrigger;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = true))
    EDungeonState mState;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
    bool bNoBattle;
    UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<APawn> enemyClassof;

    UPROPERTY()
    TArray<AActor *> enemies;
};
