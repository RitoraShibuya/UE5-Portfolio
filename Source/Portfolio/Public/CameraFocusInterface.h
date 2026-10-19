// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraFocusInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCameraFocusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PORTFOLIO_API ICameraFocusInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Portfolio|CameraFocus")
	virtual void OnStartFocus(AActor* CameraActor, float BlendTime) = 0;

	UFUNCTION(Category = "Portfolio|CameraFocus")
	virtual void OnEndFocus(AActor* CameraActor, float BlendTime) = 0;
};
