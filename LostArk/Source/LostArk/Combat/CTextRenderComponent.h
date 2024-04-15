#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "CTextRenderComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UCTextRenderComponent : public UTextRenderComponent
{
	GENERATED_BODY()
  public:
    void TextAutoOff();

  private:

};
