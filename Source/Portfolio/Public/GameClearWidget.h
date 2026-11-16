// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
};
