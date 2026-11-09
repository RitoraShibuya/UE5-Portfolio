// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileBase.h"
#include "EndTile.generated.h"


class UChildActorComponent;
class AInteractableSignalActorBase;
/**
 *
 */
UCLASS()
class PORTFOLIO_API AEndTile : public ATileBase
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> SignalActorComponent;

protected:
	AEndTile();

	virtual void BeginPlay() override;

public:
	AInteractableSignalActorBase* GetSignalActor();
};
