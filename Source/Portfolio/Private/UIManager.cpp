// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MainWidget.h"
#include "GameClearWidget.h"

UMainWidget* AUIManager::CreateMainWidget() {
	return Cast<UMainWidget>(CreateWidgetClass(MainWidgetClass));
}

UGameClearWidget* AUIManager::CreateGameClearWidget() {
	return Cast<UGameClearWidget>(CreateWidgetClass(GameClearWidgetClass));
}

UUserWidget* AUIManager::CreateWidgetClass(TSubclassOf<UUserWidget> NewWidget) {
	for (UUserWidget* Widget : CreateWidgets) {
		if (Widget->GetClass() == NewWidget) {
			return Widget;
		}
	}

	UUserWidget* TargetWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), NewWidget);

	if (TargetWidget)
	{
		TargetWidget->AddToViewport(0);
	}
	return TargetWidget;
}