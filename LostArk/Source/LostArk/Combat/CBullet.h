#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

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

public:	
	void Fire(const FVector& Direction);

};
