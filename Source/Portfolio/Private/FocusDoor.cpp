// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusDoor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GamePlayStatics.h"

AFocusDoor::AFocusDoor() {
	FocusCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Focus Camera"));
	FocusCameraComponent->SetupAttachment(RootComponent);
}

void AFocusDoor::Open() {
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (ICameraFocusInterface* Interface = Cast<ICameraFocusInterface>(PlayerController)) {
		Interface->OnStartFocus(this, 0.5);
	}

	OpenMesh();

	FTimerHandle TimeHandele;
	GetWorldTimerManager().SetTimer(
		TimeHandele,
		[this]() {
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (ICameraFocusInterface* Interface = Cast<ICameraFocusInterface>(PlayerController)) {
				Interface->OnEndFocus(this, 0.5);
			}
		},
		2.0f,
		false
		);
}

void AFocusDoor::OnStartFocus(AActor* CameraActor, float BlendTime) {

}

void AFocusDoor::OnEndFocus(AActor* CameraActor, float BlendTime) {

}