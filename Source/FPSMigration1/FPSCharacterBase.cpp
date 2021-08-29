// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "FPSGunBase.h"
#include "Kismet/GameplayStatics.h"
#include "InteractInterface.h"
// Sets default values
AFPSCharacterBase::AFPSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();


	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(PlayerCamera);

	// GunHolder = CreateDefaultSubobject<USceneComponent>(TEXT("GunParent"));
	// GunHolder->SetupAttachment(MeshComponent);

	IronSightCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("IronSightCamera"));
	IronSightCamera->SetupAttachment(MeshComponent);
	//
	// GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComponent"));
	// GunMeshComponent->SetupAttachment(GunHolder);
}

// Called when the game starts or when spawned
void AFPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AFPSGunBase>(GunClass);
	Gun->AttachToComponent(GetPlayerMeshComponent(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Gun"));
	Gun->SetOwner(this);
	this->SetActorHiddenInGame(true);
}

void AFPSCharacterBase::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AFPSCharacterBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

USkeletalMeshComponent* AFPSCharacterBase::GetPlayerMeshComponent()
{
	return MeshComponent;
}

void AFPSCharacterBase::Aim()
{
	UE_LOG(LogTemp, Warning, TEXT("Aimed!!!"));


	/*PlayerCamera->SetActive(false);
	Gun->GetIronSightCamera()->SetActive(true);
	*/
	PlayerCamera->SetActive(false);
	/*IronSightCamera->SetActive(true);*/
	//IronSightCameraPlayer->SetRelativeLocation(Gun->GetIronSightCamera()->GetRelativeLocation());
	//IronSightCameraPlayer->SetActive(true);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Gun, .2f);


}

// Called every frame
void AFPSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFPSCharacterBase::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFPSCharacterBase::StopAim);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacterBase::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacterBase::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacterBase::Reload);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &AFPSCharacterBase::DropWeapon);
}

void AFPSCharacterBase::DropWeapon()
{
	Gun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if (Gun->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		IInteractInterface::Execute_OnDropped(Gun);
	}
	
}

void AFPSCharacterBase::StopAim()
{
	PlayerCamera->SetActive(true);
	//IronSightCamera->SetActive(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(this, .2f);

}

void AFPSCharacterBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing~ FPSCharacterBase"));
	Gun->SetShouldFire(true);
	Gun->DelayFunction();
}

void AFPSCharacterBase::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping Fire~ FPSCharacterBase"));
	Gun->SetShouldFire(false);
	Gun->StopGunFire();
}

void AFPSCharacterBase::Reload()
{
	FTimerHandle ReloadTimer;
	GetWorldTimerManager().SetTimer(ReloadTimer, Gun, &AFPSGunBase::Reload, Gun->GetReloadTime(), false, Gun->GetReloadTime());
}