#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolingT.generated.h"

UCLASS()
class LOSTARK_API AObjectPoolingT : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectPoolingT();

    void Init();
    void Return(class ACBullet* target);
    class ACBullet* Pop();
	

protected:
	virtual void BeginPlay() override;

public:	

private:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    int32 mBulletPoolSize;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    TSubclassOf<class ACBullet> bulletClass;

	TQueue<ACBullet *> BulletPool;


};
