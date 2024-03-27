#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComponentBeginOverlap);


UCLASS()
class LOSTARK_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBullet();
    virtual ~ACBullet();


protected:
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ParticleData")
    class UParticleSystem *mParticle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UStaticMeshComponent *StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
    class UProjectileMovementComponent *Projectile;

	 UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UBoxComponent *mCollider;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    TSubclassOf<class ACBulletManager> mBulletPool;

	FTimerHandle ReturnHandle;


public:	
    void Fire(const FVector &Direction ,const float &firerate);
    void SetPower(const float& damage);
  
    void Init();
    
    UFUNCTION()
    void Deactivate();

private:
    //ÄÄÆ÷³ÍÆ® overlap
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

    float mdamage;
    class AController *mController;
    TArray<class ACharacter *> HittedCharacter;
};
