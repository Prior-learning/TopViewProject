#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"


UCLASS()
class LOSTARK_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	FORCEINLINE class UCameraComponent* GetCamera() { return mCamera; }
	FORCEINLINE class USpringArmComponent* GetSpring() { return mSpring; }
public:
	UFUNCTION(BlueprintCallable)
		E_WeaponType GetWeaponType();
	UFUNCTION(BlueprintCallable)
		bool IsAiming();

private:
	UFUNCTION()
		void Move_Forward(float Axis);
	UFUNCTION()
		void Move_Right(float Axis);
	UFUNCTION()
		void Look_Mouse();

	void Move_Cursor(float Axis);
	void OnEquip1();
	void OnAim();
	void OffAim();
    void BeginRoll();
    void BeginFire();
    void EndFire();


public:
    void EndRoll();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* mCamera;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* mSpring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(VisibleDefaultsOnly)
		class UCPlayerStateComponent* mPlayerState;

	UPROPERTY(VisibleDefaultsOnly)
        class UCMontageComponent *mMontages;
	
	E_WeaponType mPlayerWeaponType;

};
