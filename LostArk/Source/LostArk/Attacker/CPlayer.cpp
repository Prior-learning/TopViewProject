
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
#include "../UParticlePooling.h"

#include "Kismet/KismetMathLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "../UParticlePooling.h"
#include "../ObjectPools/CParticleManager.h"

ACPlayer::ACPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    InitMovement();
    InitCamera();
    InitCursor();
	
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
	CreateWeapon();
    mPlayerState->SetUnarmed();

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CursorUpdate();

	if (IsAiming() == true)
		Look_Mouse();
    
	if (mPlayerState->IsFireMode())
    {
        mTickTimer += DeltaTime;
    }
    if (mTickTimer >= mGun->GetFireRate())
    {
        mTickTimer = 0;
        Attack();
    }
}



E_WeaponType ACPlayer::GetWeaponType()
{
	return mPlayerState->GetWeaponType();
}

bool ACPlayer::IsAiming()
{
	return mPlayerState->IsAimMode();
}

void ACPlayer::Move_Forward(float Axis)
{
    FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
    FVector direction = FQuat(rotator).GetForwardVector();
    AddMovementInput(direction, Axis);
    //UE_LOG(LogTemp, Warning, TEXT("[CRifle::Fire]"));
}

void ACPlayer::Move_Right(float Axis)
{
    FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
    FVector direction = FQuat(rotator).GetRightVector();
    AddMovementInput(direction, Axis);
}

void ACPlayer::OnEquip1()
{
    if (GetWeaponType() == E_WeaponType::UnArmed)
    {
        mPlayerState->SetPrimary();
        mGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),mGun->GetHandSocket());
    }
    else
    {
        mPlayerState->SetUnarmed();
        mGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),mGun->GetHolsterSocket());
    }

}
void ACPlayer::OnAim()
{
    CheckTrue(mPlayerState->IsContains(E_State::Aim));
    CheckTrue(IsAiming());
    CheckTrue(GetWeaponType() == E_WeaponType::UnArmed);
    mPlayerState->SetAim();
    GetCharacterMovement()->MaxWalkSpeed = 250;
}
void ACPlayer::OffAim()
{
    CheckFalse(IsAiming());
    mPlayerState->UnSetAim();
    GetCharacterMovement()->MaxWalkSpeed = 600;
}
void ACPlayer::BeginRoll()
{
    CheckTrue(mPlayerState->IsContains(E_State::Roll));
    FVector start = GetActorLocation();
    FVector from = start + GetVelocity().GetSafeNormal2D();
    SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from));
    GetCharacterMovement()->MaxWalkSpeed = 1200;
    mMontages->PlayAnimMontage(EMontage_State::Roll);
    mPlayerState->SetRoll();
    OffCollision();
}
void ACPlayer::EndRoll()
{
    GetCharacterMovement()->MaxWalkSpeed = 600;
    mPlayerState->UnSetRoll();
    OnCollision();
}
void ACPlayer::CreateWeapon()
{
    CheckNull(mWeaponClass);
	// 업캐스팅 다운캐스팅...은 너무 위험하고 다형성이없음
    mGun = Cast<ACGun>(ACWeapon::CreateWeapon(GetWorld(), mWeaponClass, this));
}
void ACPlayer::OnCollision()
{
    GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}
void ACPlayer::OffCollision()
{
    GetCapsuleComponent()->SetGenerateOverlapEvents(false);
}
void ACPlayer::Attack()
{
    mGun->Fire(this);
    mMontages->PlayAnimMontage(EMontage_State::Attack);
}
void ACPlayer::BeginFire()
{
    CheckTrue(mPlayerState->IsContains(E_State::Attack));
    CheckFalse(IsAiming());
    mPlayerState->SetFire();
}

void ACPlayer::EndFire()
{
    mPlayerState->UnSetFire();
}



void ACPlayer::InitMovement()
{
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void ACPlayer::InitCamera()
{
    mSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
    mSpring->SetupAttachment(RootComponent);
    mSpring->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
    mSpring->TargetArmLength = 1000.f;
    mSpring->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    mSpring->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    mCamera->SetupAttachment(mSpring, USpringArmComponent::SocketName);
    mCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ACPlayer::InitCursor()
{
    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
    CursorToWorld->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(
        TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
    if (DecalMaterialAsset.Succeeded())
    {
        CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
    }
    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

void ACPlayer::CursorUpdate()
{
    if (CursorToWorld != nullptr)
    {
        if (APlayerController *PC = Cast<APlayerController>(GetController()))
        {
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            FVector CursorFV = TraceHitResult.ImpactNormal;
            FRotator CursorR = CursorFV.Rotation();
            CursorToWorld->SetWorldLocation(TraceHitResult.Location);
            CursorToWorld->SetWorldRotation(CursorR);
        }
    }
}
void ACPlayer::Look_Mouse()
{
    if (APlayerController *PC = Cast<APlayerController>(GetController()))
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
    if (APlayerController *PC = Cast<APlayerController>(GetController()))
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


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::Move_Right);

	PlayerInputComponent->BindAction("Equip1", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip1);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
    PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::BeginRoll);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::BeginFire);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::EndFire);
}

void ACPlayer::Damaged(float Damage, FDamageEvent &Event, AController *controller, AActor *causer,
                       const FVector hitLocation, UParticleSystem *particle)
{
    TakeDamage(Damage, Event, controller, causer);
    AUParticlePooling *temp = ACParticleManager::Get().GetParticle();
    CheckNull(temp);
    if (particle == nullptr)
    {
        CLog::Log("particle is Nullptr");
        return;
    }
    temp->SetActorLocation(hitLocation);
    temp->SetParticle(particle);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                           AActor *DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    mMontages->PlayAnimMontage(EMontage_State::Hitted);
    return 10.f;
}


           


