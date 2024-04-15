#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDamageText.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARK_API UCDamageText : public UActorComponent
{
    GENERATED_BODY()

  public:
    UCDamageText();

  protected:
    virtual void BeginPlay() override;

  public:
    void TextRender(float damage,const FVector& location);
  private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 mPoolTextSize = 6;
   
    TArray<class UCTextRenderComponent *> mTextVec;
    int32 midx = -1;

    

};
