
#include "CPlayer.h"
#include "../Global.h"


#include "UObject/ConstructorHelpers.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"
#include "../ActorComponent/CMontageComponent.h"

#include "../Combat/CWeapon.h"
#include "../Combat/CGun.h"


#include "Kismet/KismetMathLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"


ACPlayer::ACPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create Spring
	mSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	mSpring->SetupAttachment(RootComponent);
	mSpring->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	mSpring->TargetArmLength = 900.f;
	mSpring->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	mSpring->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level


	// Create a camera...
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpring, USpringArmComponent::SocketName);
	mCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CHelpers::CreateActorComponent<UCPlayerStateComponent>(this, &mPlayerState, "PlayerStateComponent");
    CHelpers::CreateActorComponent<UCMontageComponent>(this, &mMontages, "Montage");
    mTickTimer = 0;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(mPlayerState);
	mPlayerState->SetUnarmed();
	mPlayerState->UnSetAiming();
    mPlayerState->UnSetFiring();
	CreateWeapon();

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CursorToWorld != nullptr)
	{
		/*if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = mCamera->GetComponentLocation();
				FVector EndLocation = mCamera->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}*/

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);

		}
	}
	if (IsAiming() == true)
		Look_Mouse();
    //현재틱을 계속 업데이트
    
	if (mPlayerState->IsFiring())
    {
        mTickTimer += DeltaTime;
    }
    if (mTickTimer >= mGun->GetFireRate())
    {
        mTickTimer = 0;
        Fire();
    }
}



E_WeaponType ACPlayer::GetWeaponType()
{
	return mPlayerState->GetWeaponType();
}

bool ACPlayer::IsAiming()
{
	return mPlayerState->IsAiming();
}

void ACPlayer::Move_Forward(float Axis)
{
	//FVector Direction = FVector::ForwardVector;
    FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
    FVector direction = FQuat(rotator).GetForwardVector();
    AddMovementInput(direction, Axis);
}

void ACPlayer::Move_Right(float Axis)
{
	//FVector Direction = FVector::RightVector;
    FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
    FVector direction = FQuat(rotator).GetRightVector();
    AddMovementInput(direction, Axis);
}

void ACPlayer::Look_Mouse()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector Cursor_pos = TraceHitResult.Location;
		FVector pos = GetActorLocation();
		FVector direction = Cursor_pos - pos;
		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(pos, FVector(Cursor_pos.X, Cursor_pos.Y, pos.Z));
		SetActorRotation(LookRotation);
	}

}

void ACPlayer::Move_Cursor(float Axis)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector Cursor_pos = TraceHitResult.Location;
		FVector pos = GetActorLocation();
		FVector direction = Cursor_pos - pos;
		float distance = sqrt(direction.X * direction.X + direction.Y * direction.Y);
		direction.X = direction.X / distance;
		direction.Y = direction.Y / distance;
		AddMovementInput(direction, Axis);
	}
}
void ACPlayer::OnEquip1()
{
    if (GetWeaponType() == E_WeaponType::UnArmed)
    {
        mPlayerState->SetPrimary();
        mGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
                                mGun->GetHandSocket());
    }
    else
    {
        mPlayerState->SetUnarmed();
        mGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
                                mGun->GetHolsterSocket());
    }

}
void ACPlayer::OnAim()
{

    if (!mPlayerState->IsContains(E_State::Aim) &&!IsAiming() && GetWeaponType() != E_WeaponType::UnArmed)
    {
        mPlayerState->SetAiming();
        GetCharacterMovement()->MaxWalkSpeed = 250;
    }
}
void ACPlayer::OffAim()
{
    if (IsAiming())
    {
        mPlayerState->UnSetAiming();
        GetCharacterMovement()->MaxWalkSpeed = 600;
    }
}
void ACPlayer::BeginRoll()
{
	//checktrue로 변경해도 될듯
    if (!mPlayerState->IsContains(E_State::Roll))
    {
        FVector start = GetActorLocation();
        FVector from = start + GetVelocity().GetSafeNormal2D();
        SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from));
        GetCharacterMovement()->MaxWalkSpeed = 1200;
        mMontages->PlayAnimMontage(EMontage_State::Roll);
        mPlayerState->Add(E_State::Aim, E_WHY_BLOCKED::ROLLING);
        mPlayerState->Add(E_State::Attack, E_WHY_BLOCKED::ROLLING);
        mPlayerState->Add(E_State::Reload, E_WHY_BLOCKED::ROLLING);
        mPlayerState->Add(E_State::Roll, E_WHY_BLOCKED::ROLLING);

    }
}
void ACPlayer::EndRoll()
{
    GetCharacterMovement()->MaxWalkSpeed = 600;
    mPlayerState->Remove(E_State::Aim, E_WHY_BLOCKED::ROLLING);
    mPlayerState->Remove(E_State::Attack, E_WHY_BLOCKED::ROLLING);
    mPlayerState->Remove(E_State::Reload, E_WHY_BLOCKED::ROLLING);
    mPlayerState->Remove(E_State::Roll, E_WHY_BLOCKED::ROLLING);
}
void ACPlayer::CreateWeapon()
{
    CheckNull(mWeaponClass);

    mGun = ACGun::CreateWeapon(GetWorld(), mWeaponClass, this);
}
void ACPlayer::OnCollision()
{
	//인터페이스라서 오버라이드만 해둠
}
void ACPlayer::OffCollision()
{
    //인터페이스라서 오버라이드만 해둠
}
void ACPlayer::BeginFire()
{
    CheckTrue(mPlayerState->IsContains(E_State::Attack));
    CheckFalse(IsAiming());
    mPlayerState->SetFiring();
    mPlayerState->Add(E_State::Reload, E_WHY_BLOCKED::ATTACKING);
}

void ACPlayer::EndFire()
{
    mPlayerState->UnSetFiring();
    mPlayerState->Remove(E_State::Reload, E_WHY_BLOCKED::ATTACKING);
}

void ACPlayer::Fire()
{
    mGun->Fire(this);
    mMontages->PlayAnimMontage(EMontage_State::Attack);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("Mouse_RB", this, &ACPlayer::Move_Cursor);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::Move_Right);

	PlayerInputComponent->BindAction("Equip1", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip1);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
    PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::BeginRoll);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::BeginFire);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::EndFire);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                           AActor *DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    mMontages->PlayAnimMontage(EMontage_State::Hitted);
    return 10.f;
}


           


