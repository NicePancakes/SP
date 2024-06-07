#include "Player/SPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SPCharacterMovementComponent.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "Weapons/SPBaseWeapon.h"


ASPBaseCharacter::ASPBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USPHealthComponent>(TEXT("HealthComponent"));
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<USPWeaponComponent>(TEXT("WeaponComponent"));

	HealthComponent->GetOnDeath().AddUObject(this, &ThisClass::OnDeath);
	HealthComponent->GetOnHealthChanged().AddUObject(this, &ThisClass::OnHealthChanged);
	LandedDelegate.AddUniqueDynamic(this, &ThisClass::OnGroundLanded);
}

void ASPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
}

void ASPBaseCharacter::MoveForward(float Amount)
{
	if(Amount == 0.0f) { return; }
	AddMovementInput(GetActorForwardVector(), Amount);
	bIsMoveForward = Amount > 0.0f;
}

void ASPBaseCharacter::MoveRight(float Amount)
{
	if(Amount == 0.0f) { return; }
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASPBaseCharacter::OnStartRunning()
{
	bIsWantRun = true;
}

void ASPBaseCharacter::OnStopRunning()
{
	bIsWantRun = false;
}

void ASPBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeTime);

	if(IsValid(Controller))
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponComponent->StopFire();
}

void ASPBaseCharacter::OnHealthChanged(float NewHealth)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}

void ASPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const float FallVelocity = -GetCharacterMovement()->Velocity.Z;

	if(FallVelocity < LandedDamageVelocity.X) { return; }

	const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}



void ASPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ThisClass::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ThisClass::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent.Get(), &USPWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent.Get(), &USPWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent.Get(), &USPWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent.Get(), &USPWeaponComponent::Reload);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ThisClass::AddControllerYawInput);

}

bool ASPBaseCharacter::IsRunning() const
{
	return bIsWantRun && bIsMoveForward && !GetVelocity().IsZero();
}

float ASPBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero()) { return 0.0f; }

	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

