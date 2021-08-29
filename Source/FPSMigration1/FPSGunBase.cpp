// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "COmponents/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
// Sets default values
AFPSGunBase::AFPSGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunComponent"));
	//SetRootComponent(Root);
	SetRootComponent(GunMeshComponent);
	//GunMeshComponent->SetupAttachment(Root);

	IronSight = CreateDefaultSubobject<UCameraComponent>(TEXT("IronSightCamera"));
	IronSight->SetupAttachment(GunMeshComponent);

}

// Called when the game starts or when spawned
void AFPSGunBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<AFPSCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn init failed"));
	}
	PlayerController = PlayerPawn->GetController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController init failed"));
	}

	MaxMagazineSize = MagazineSize;
	
	bIsReloading = false;
}

// Called every frame
void AFPSGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UCameraComponent* AFPSGunBase::GetIronSightCamera()
{
	return IronSight;
}

USkeletalMeshComponent* AFPSGunBase::GetGunMeshComponent()
{
	return GunMeshComponent;
}

void AFPSGunBase::GunFire()
{
	if (bIsReloading)
	{
		return;
	}
	if (MagazineSize > 0)
	{
		FTransform MuzzleTransform = GunMeshComponent->GetSocketTransform(TEXT("Muzzle"));
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector End = CameraLocation + CameraRotation.Vector() * maxRange;
		FHitResult hit;

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(this);
		queryParams.AddIgnoredActor(GetOwner());

		DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Red, true);

		bool bCast = GetWorld()->LineTraceSingleByChannel(hit, CameraLocation, End, ECollisionChannel::ECC_EngineTraceChannel2, queryParams);

		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlashParticle, MuzzleTransform);

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticle, GunMeshComponent, TEXT("Muzzle"));
		UGameplayStatics::PlaySound2D(GetWorld(), FireSoundBase);
		if (bCast)
		{
			UE_LOG(LogTemp, Warning, TEXT("Suxesful"));
		}
		MagazineSize = MagazineSize - 1;
		UE_LOG(LogTemp, Error, TEXT("%d bullets left"), MagazineSize);
		UE_LOG(LogTemp, Error, TEXT("%d Total Ammunition left"), CurrentAmmo);
	}
	else
	{
		StopGunFire();
		if (CurrentAmmo > 0)
		{
			GetWorldTimerManager().SetTimer(ReloadTimer, this, &AFPSGunBase::Reload, ReloadTime, false, ReloadTime);
			UE_LOG(LogTemp, Error, TEXT("Timer should Start"));
			bIsReloading = true;
		}
	}
}

void AFPSGunBase::StopGunFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AFPSGunBase::DelayFunction()
{
	if (bShouldFire)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSGunBase::GunFire, .1f, true, .01f);

	}
}

void AFPSGunBase::SetShouldFire(bool bS)
{
	bShouldFire = bS;
}

void AFPSGunBase::Reload()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	UE_LOG(LogTemp, Error, TEXT("ReloadTriggered"))
	while (MagazineSize < MaxMagazineSize)
	{
		if (CurrentAmmo == 0)
		{
			return;
		}
		MagazineSize = MagazineSize + 1;
		CurrentAmmo = CurrentAmmo - 1;
		UE_LOG(LogTemp, Error, TEXT("Reload Working"))
	}
	UE_LOG(LogTemp, Error, TEXT("Reload Complete"));
	GetWorldTimerManager().ClearTimer(ReloadTimer);
	bIsReloading = false;
}

float AFPSGunBase::GetReloadTime()
{
	return ReloadTime;
}

void AFPSGunBase::OnDropped_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("It works, somehow"))
}

