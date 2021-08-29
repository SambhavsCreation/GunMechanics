// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "FPSGunBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(GetCapsuleComponent());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());

	GunHolder = CreateDefaultSubobject<USceneComponent>(TEXT("GunHolder"));
	GunHolder->SetupAttachment(PlayerCamera);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AFPSGunBase>(GunClass);
	Gun->AttachToComponent(GunHolder, FAttachmentTransformRules::KeepRelativeTransform);
	Gun->SetOwner(this);
	this->SetActorHiddenInGame(true);
}

void AFPSCharacter::Aim()
{
	PlayerCamera->SetActive(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Gun, .2f);
}

void AFPSCharacter::StopAim()
{
	PlayerCamera->SetActive(true);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(this, .2f);
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFPSCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFPSCharacter::StopAim);
}

void AFPSCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

