// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IGun.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIGun : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * Intended to use as headder but will set Tags for Interactables here:
Gun
Player
Enemy
?
 *
 */
class VRTEST_V1_API IIGun
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IClass")
		void Shoot();
	
};
