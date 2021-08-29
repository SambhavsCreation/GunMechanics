// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSMIGRATION1_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseInteraction")
	void OnDropped();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseInteraction")
	void OnInteract();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseInteraction")
	void OnEnterInteractionRadius();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseInteraction")
	void OnExitInteractionRadius();
};
