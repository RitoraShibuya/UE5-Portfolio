// Copyright Epic Games, Inc. All Rights Reserved.


#include "PortfolioPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "PortfolioCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Portfolio.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "MainUI.h"
#include "Kismet/GamePlayStatics.h"

APortfolioPlayerController::APortfolioPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = APortfolioCameraManager::StaticClass();
}

void APortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController()) {

		//MainUI生成
		MainUI = CreateWidget<UMainUI>(this, MainUIWidgetClass);

		if (MainUI)
		{
			MainUI->AddToPlayerScreen(0);
		}

		// only spawn touch controls on local player controllers
		if (ShouldUseTouchControls())
		{
			// spawn the mobile controls widget
			MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

			if (MobileControlsWidget)
			{
				// add the controls to the player screen
				MobileControlsWidget->AddToPlayerScreen(0);

			}
			else {

				UE_LOG(LogPortfolio, Error, TEXT("Could not spawn mobile controls widget."));

			}

		}
	}
}

void APortfolioPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

bool APortfolioPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void APortfolioPlayerController::OnStartFocus(AActor* CameraActor,float BlendTime) {
	SetViewTargetWithBlend(
		CameraActor,
		BlendTime,
		EViewTargetBlendFunction::VTBlend_Cubic,
		0.0f,
		false);
}

void APortfolioPlayerController::OnEndFocus(AActor* CameraActor, float BlendTime) {
	SetViewTargetWithBlend(
		this,
		BlendTime,
		EViewTargetBlendFunction::VTBlend_Linear,
		0.0f,
		false);
}