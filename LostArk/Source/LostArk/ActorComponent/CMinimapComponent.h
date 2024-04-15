// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMinimapComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCMinimapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMinimapComponent();

protected:
	virtual void BeginPlay() override;

private:
    void Initialize();
  public:	
<<<<<<< HEAD

public:	
=======
>>>>>>> Dorong
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category="Minimap")
    class USpringArmComponent *mSpring;
    UPROPERTY(EditAnywhere, Category = "Minimap")
    class USceneCaptureComponent *mCamera;
};
