#pragma once

#include "CoreMinimal.h"
#include "../Combat/ICombat.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"


UCLASS()
class LOSTARK_API ACPlayer : public ACharacter, public IICombat, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Damaged(float Damage, FDamageEvent &Event, AController *controller, AActor *causer,
                         const FVector hitLocation, class UParticleSystem *particle) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                             AActor *DamageCauser) override;

  public:
	FORCEINLINE class UCameraComponent* GetCamera() { return mCamera; }
	FORCEINLINE class USpringArmComponent* GetSpring() { return mSpring; }
public:
	UFUNCTION(BlueprintCallable)
		E_WeaponType GetWeaponType();
	UFUNCTION(BlueprintCallable)
		bool IsAiming();
    UFUNCTION(BlueprintCallable)
    bool IsCanMove();

	void OnAirborn();
    void OffAirborn();


private:
	UFUNCTION()
		void Look_Mouse();

	void OnEquip1();
    void OnEquip2();
    void OnEquip3();
    void UnEquip();
    void SetWeapon(E_WeaponType InType);

	void OnAim();
	void OffAim();
    void BeginRoll();
	void BeginFire();
    void EndFire();

	void OnFSkill();
    void OffFSkill();

	void OnESkill();
    void OffESkill();

    void InitMovement();
    void InitCamera();
  
public:
    void EndRoll();
    virtual FGenericTeamId GetGenericTeamId() const override{return mTeamID;}

private:
  virtual void CreateWeapon() override;
  virtual void OnCollision() override;
  virtual void OffCollision() override;
  virtual void Attack() override;


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* mCamera;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* mSpring;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCPlayerStateComponent* mPlayerState;
    
	UPROPERTY(VisibleDefaultsOnly)
    class UCPSkillComponent *mPlayerSkill2;

	UPROPERTY(VisibleDefaultsOnly)
        class UCMontageComponent *mMontages;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
        TSubclassOf<class ACWeapon> mWeaponClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
        TSubclassOf<class ACWeapon> mWeaponClass2;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
        TSubclassOf<class ACWeapon> mWeaponClass3;

    class ACGun *mGun;
    class ACGun *mShotGun;
    class ACGun *mSniper;

    FGenericTeamId mTeamID = 0;
	E_WeaponType mPlayerWeaponType;

	float CurrentFirerate;
    FTimerHandle FireDelay;

};
