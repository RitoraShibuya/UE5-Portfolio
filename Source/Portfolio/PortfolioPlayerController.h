// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraFocusInterface.h"
#include "PortfolioPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

class UMainUI;
class UShooterBulletCounterUI;
/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config="Game")
class PORTFOLIO_API APortfolioPlayerController : public APlayerController, public ICameraFocusInterface
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	APortfolioPlayerController();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/*メインUIクラス*/
	UPROPERTY(EditAnywhere,Category = "Portfolio|UI")
	TSubclassOf<UUserWidget> MainUIWidgetClass;

	/*メインUIのポインタ*/
	UPROPERTY()
	TObjectPtr<UMainUI> MainUI;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	virtual void OnStartFocus(AActor* CameraActor, float BlendTime);

	virtual void OnEndFocus(AActor* CameraActor, float BlendTime);

};
