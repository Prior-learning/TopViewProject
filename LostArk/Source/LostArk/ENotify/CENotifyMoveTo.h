#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CENotifyMoveTo.generated.h"


UENUM(BlueprintType)
enum class EDirection : uint8
{
	Forward,
	Back,
	Right,
	Left,
	Max,
};
UCLASS()
class LOSTARK_API UCENotifyMoveTo : public UAnimNotify
{
	GENERATED_BODY()
	
	public:
	virtual FString GetNotifyName() const;
    virtual void Notify(class USkeletalMeshComponent *MeshComp, class UAnimSequenceBase *Animation);

	protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameter")
    EDirection mDirection = EDirection::Forward;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
    float mDistance = 50.f;

};
