// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class FPSMIGRATION1_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interaction Functions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnDropped();
	virtual void OnDropped_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnEnterInteractionRadius();
	virtual void OnEnterInteractionRadius_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnExitInteractionRadius();
	virtual void OnExitInteractionRadius_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category = "MyCategory")
	void OnInteract();
	virtual void OnInteract_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractDetectionRadius;

};
