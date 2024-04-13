#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMarkComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCMarkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCMarkComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Mark")
    class UPaperSpriteComponent *mSprite;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Mark")
    FVector mScale = {1,1,1};
};
