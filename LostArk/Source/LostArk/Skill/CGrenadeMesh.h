#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGrenadeMesh.generated.h"

UCLASS()
class LOSTARK_API ACGrenadeMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGrenadeMesh();

protected:
	virtual void BeginPlay() override;

	 UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    class UStaticMeshComponent *GMesh;

	 UPROPERTY(VisibleDefaultsOnly)
    class UProjectileMovementComponent *Projectile;

public:	
	void Throwing();


};
