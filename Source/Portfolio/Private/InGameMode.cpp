// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "GameFramework/PlayerController.h"
#include "UIManager.h"
#include "GameClearWidget.h"

void AInGameMode::OnGameClear() {
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if(Controller){
		AUIManager* HUD = Cast<AUIManager>(Controller->GetHUD());
		if (HUD) {
			UGameClearWidget* GameClearWidget = HUD->CreateGameClearWidget();
		}
	}
}
