// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "CameraFocusInterface.h"
#include "FocusDoor.generated.h"

/**
 *
 */
class UCameraComponent;
class APlayerController;

UCLASS()
class PORTFOLIO_API AFocusDoor : public ADoorBase, public ICameraFocusInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TObjectPtr<UCameraComponent> FocusCameraComponent;

private:

public:
	AFocusDoor();
protected:
	virtual void OnInteract(AActor* InteractActor) override;

	virtual void OnStartFocus(AActor* CameraActor, float BlendTime);

	virtual void OnEndFocus(AActor* CameraActor, float BlendTime);
};
