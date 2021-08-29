// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/SphereComponent.h"
// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractDetectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionRadius"));

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnDropped_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("It works, somehow"))
	InteractDetectionRadius->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItemBase::OnEnterInteractionRadius_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction Range Entered"))
}

void AItemBase::OnExitInteractionRadius_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction Range Exited"))
}

void AItemBase::OnInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted"))
	Destroy();
}

