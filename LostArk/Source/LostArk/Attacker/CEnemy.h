#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class LOSTARK_API ACEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UCapsuleComponent* capsule;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class USkeletalMeshComponent* Mesh;
};
