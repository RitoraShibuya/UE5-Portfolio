// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIManager.generated.h"

class UUserWidget;
class UMainWidget;
class UGameClearWidget;
/**
 * 
 */
UCLASS()
class PORTFOLIO_API AUIManager : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Portfolio|UI")
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Portfolio|UI")
	TSubclassOf<UUserWidget> GameClearWidgetClass;

	TArray<UUserWidget*> CreateWidgets;
public:
	UMainWidget* CreateMainWidget();
	UGameClearWidget* CreateGameClearWidget();

private:
	UUserWidget* CreateWidgetClass(TSubclassOf<UUserWidget> NewWidget);
};
