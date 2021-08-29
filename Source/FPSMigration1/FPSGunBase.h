// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractInterface.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "FPSGunBase.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UCapsuleComponent;
class UParticleSystem;
class USpringArmComponent;
class USoundBase;

UCLASS()
class FPSMIGRATION1_API AFPSGunBase : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* IronSight;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		float maxRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		float ShotDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* MuzzleFlashParticle;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		USoundBase* FireSoundBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		int32 MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		int32 MaxMagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDetails", meta = (AllowPrivateAccess = "true"))
		float ReloadTime;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		UCameraComponent* GetIronSightCamera();

	UFUNCTION(BlueprintCallable)
		USkeletalMeshComponent* GetGunMeshComponent();

	UFUNCTION(BlueprintCallable)
		void GunFire();

	UFUNCTION(BlueprintCallable)
		void StopGunFire();

	UFUNCTION()
		void DelayFunction();

	UFUNCTION()
		void SetShouldFire(bool bS);

	UFUNCTION()
		void Reload();

	UFUNCTION()
		float GetReloadTime();

	void OnInteract();
	virtual void OnInteract_Implementation() override;


private:

	APawn* PlayerPawn;
	AController* PlayerController;
	bool bShouldFire;
	bool bIsReloading;
	FTimerHandle ReloadTimer;


};
