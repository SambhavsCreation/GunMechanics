// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacterBase.generated.h"

class AFPSGunBase;
class UCameraComponent;
class USceneComponent;
class USkeletalMesh;
class UAnimBlueprint;
class USkeletalMeshComponent;
UCLASS()
class FPSMIGRATION1_API AFPSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	USkeletalMeshComponent* GetPlayerMeshComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Holder", meta = (AllowPrivateAccess = "true"))
	USceneComponent* GunHolder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* IronSightCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFPSGunBase> GunClass;
	
	UPROPERTY()
	AFPSGunBase* Gun;

	virtual void Aim();

	virtual void StopAim();


	UFUNCTION()
		void Fire();
	UFUNCTION()
		void StopFire();
	UFUNCTION()
		void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void DropWeapon();


};
