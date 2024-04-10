
#include "CPlayer.h"
#include "../Global.h"


#include "UObject/ConstructorHelpers.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "../ActorComponent/CPlayerStateComponent.h"
#include "../ActorComponent/CMontageComponent.h"
#include "../ActorComponent/CPSkillComponent.h"

#include "../LostArkPlayerController.h"

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
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

   	CHelpers::CreateActorComponent<UCPSkillComponent>(this, &mPlayerSkill, "PlayerSkillComponent");
	CHelpers::CreateActorComponent<UCPlayerStateComponent>(this, &mPlayerState, "PlayerStateComponent");
    CHelpers::CreateActorComponent<UCMontageComponent>(this, &mMontages, "Montage");
    CurrentFirerate = 0;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(mPlayerState);
    CheckNull(mPlayerSkill);
    CheckNull(mMontages);

	CreateWeapon();
    OnEquip1();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAiming() == true)
    {
        Look_Mouse();
    }
    /*if (!mPlayerState->IsCanMove())
    {
        GetCharacterMovement()->MaxWalkSpeed=0;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 600;
    }*/
}

E_WeaponType ACPlayer::GetWeaponType()
{
	return mPlayerState->GetWeaponType();
}

bool ACPlayer::IsAiming()
{
	return mPlayerState->IsAimMode();
}

bool ACPlayer::IsCanMove()
{
    return mPlayerState->IsCanMove();
}

void ACPlayer::OnEquip1()
{
    SetWeapon(E_WeaponType::Primary);
    CurrentFirerate = mGun->GetFireRate();
    mGun->Equip(this);
}

void ACPlayer::OnEquip2()
{
    SetWeapon(E_WeaponType::Secondary);
    CurrentFirerate = mShotGun->GetFireRate();
    mShotGun->Equip(this);
}

void ACPlayer::OnEquip3()
{
    SetWeapon(E_WeaponType::Third);
    CurrentFirerate = mSniper->GetFireRate();
    mSniper->Equip(this);
}

void ACPlayer::UnEquip()
{
    switch (GetWeaponType())
    {
    case E_WeaponType::Primary:
        mGun->UnEquip(this);
        break;
    case E_WeaponType::Secondary:
        mShotGun->UnEquip(this);
        break;
    case E_WeaponType::Third:
        mSniper->UnEquip(this);
        break;
    default:
        break;
    }
}

void ACPlayer::SetWeapon(E_WeaponType InType)
{
    if (GetWeaponType() == InType)
    {
        return;
    }
    else 
    {
        UnEquip();
    }
    mPlayerState->SetWeaponType(InType);
}

void ACPlayer::SetWeaponHand()
{
    switch (GetWeaponType())
    {
    case E_WeaponType::Primary:
        mGun->Equip(this);
        break;
    case E_WeaponType::Secondary:
        mShotGun->Equip(this);
        break;
    case E_WeaponType::Third:
        mSniper->Equip(this);
        break;
    default:
        break;
    }
}

void ACPlayer::SetWeaponTemp()
{
    switch (GetWeaponType())
    {
    case E_WeaponType::Primary:
        mGun->SetHandTemp(this);
        break;
    case E_WeaponType::Secondary:
        mShotGun->SetHandTemp(this);
        break;
    case E_WeaponType::Third:
        mSniper->SetHandTemp(this);
        break;
    default:
        break;
    }
}

void ACPlayer::OnAim()
{
    CheckTrue(mPlayerState->IsContains(E_State::Aim));
    CheckTrue(IsAiming());
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
    CheckNull(mWeaponClass2);
    CheckNull(mWeaponClass3);

	// 업캐스팅 다운캐스팅...은 너무 위험하고 다형성이없음
    mGun = Cast<ACGun>(ACWeapon::CreateWeapon(GetWorld(), mWeaponClass, this));
    mShotGun = Cast<ACGun>(ACWeapon::CreateWeapon(GetWorld(), mWeaponClass2, this));
    mSniper = Cast<ACGun>(ACWeapon::CreateWeapon(GetWorld(), mWeaponClass3, this));
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
    switch (GetWeaponType())
    {
    case E_WeaponType::Primary:
        mGun->Fire(this);
        if (!mGun->GetCoolDown())
        mMontages->PlayAnimMontage(EMontage_State::Attack);
        break;
    case E_WeaponType::Secondary:
        mShotGun->Fire(this);
        if (!mShotGun->GetCoolDown())
        mMontages->PlayAnimMontage(EMontage_State::Attack);
        break;
    case E_WeaponType::Third:
        mSniper->Fire(this);
        if (!mSniper->GetCoolDown())
            mMontages->PlayAnimMontage(EMontage_State::Attack);
        break;
    case E_WeaponType::Sniping:
        if (APlayerController *PC = Cast<APlayerController>(GetController()))
        {
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            FVector Cursor_pos = TraceHitResult.Location;
            
        }
        break;
    }
}

void ACPlayer::BeginFire()
{
    CheckTrue(mPlayerState->IsContains(E_State::Attack));
    CheckFalse(IsAiming());
    mPlayerState->SetFire(); 
    Attack();
    GetWorld()->GetTimerManager().SetTimer(FireDelay, this, &ACPlayer::Attack, CurrentFirerate, true);
}

void ACPlayer::EndFire()
{
    mPlayerState->UnSetFire();
    if (GetWorld()->GetTimerManager().IsTimerActive(FireDelay))
    {
        GetWorld()->GetTimerManager().ClearTimer(FireDelay);
    }
}

void ACPlayer::OnAirborn()
{
    mPlayerState->SetAirborn();
}

void ACPlayer::OffAirborn()
{
    mPlayerState->UnSetAirborn();
}

void ACPlayer::OnFSkill()
{
    mPlayerSkill->OnSkill(ESkillButton::F);
}

void ACPlayer::OnESkill()
{
    mPlayerSkill->OnSkill(ESkillButton::E);
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

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Equip1", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip1);
    PlayerInputComponent->BindAction("Equip2", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip2);
    PlayerInputComponent->BindAction("Equip3", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip3);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
    PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::BeginRoll);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::BeginFire);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::EndFire);
    PlayerInputComponent->BindAction("FSkill", EInputEvent::IE_Pressed, this, &ACPlayer::OnFSkill);
    PlayerInputComponent->BindAction("ESkill", EInputEvent::IE_Pressed, this, &ACPlayer::OnESkill);
}

void ACPlayer::Damaged(float Damage, FDamageEvent &Event, AController *controller, AActor *causer,
                       const FVector hitLocation, UParticleSystem *particle)
{
    TakeDamage(Damage, Event, controller, causer);

    if (particle != nullptr)
    {
        AUParticlePooling *temp = ACParticleManager::Get().GetParticle();
        CheckNull(temp);

        temp->SetActorLocation(hitLocation);
        temp->SetParticle(particle);
    }
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator,
                           AActor *DamageCauser)
{
    if (DamageAmount < 0)
    {
        Super::TakeDamage(-DamageAmount, DamageEvent, EventInstigator, DamageCauser);
        mMontages->PlayAnimMontage(EMontage_State::AirBorne);
    }
    else if (0 < DamageAmount)
    {
        Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
        mMontages->PlayAnimMontage(EMontage_State::Hitted);
    }
    return 10.f;
}



// void ACPlayer::Move_Cursor(float Axis)
//{
//    if (APlayerController *PC = Cast<APlayerController>(GetController()))
//    {
//        FHitResult TraceHitResult;
//        PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
//        FVector Cursor_pos = TraceHitResult.Location;
//        FVector pos = GetActorLocation();
//        FVector direction = Cursor_pos - pos;
//        float distance = sqrt(direction.X * direction.X + direction.Y * direction.Y);
//        direction.X = direction.X / distance;
//        direction.Y = direction.Y / distance;
//        AddMovementInput(direction, Axis);
//    }
//}
// void ACPlayer::InitCursor()
//{
//    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
//    CursorToWorld->SetupAttachment(RootComponent);
//    static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(
//        TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
//    if (DecalMaterialAsset.Succeeded())
//    {
//        CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
//    }
//    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
//    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
//}

           


