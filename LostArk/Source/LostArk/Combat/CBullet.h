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

protected:
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UStaticMeshComponent *StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
    class UProjectileMovementComponent *Projectile;

	 UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UBoxComponent *mCollider;

	 UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Info")
    float mBulletDamage = 1.f;

	FTimerHandle ReturnHandle;


public:	
	void TempCreate(UWorld *world, TSubclassOf<class ACBullet> classof, ACharacter *owner);
	void Fire(const FVector& Direction);
    void TempDelete();

private:
    //������Ʈ overlap
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult &SweepResult);
    //blocking collision �� �ִ� ���(mesh ���� ��ġ�� �ʴ�) ����� event�� hit�� ���.
    UFUNCTION()
    void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
               FVector NormalImpulse, const FHitResult &Hit);

    class AController *mController;
};
