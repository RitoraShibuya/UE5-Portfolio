// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileBase.h"
#include "StartTile.generated.h"

class UChildActorComponent;
class ADoorBase;
class URectLightComponent;
/**
 * 
 */
UCLASS()
class PORTFOLIO_API AStartTile : public ATileBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DoorActorComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> LightActorComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> PickupActorComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> ClearAreaActorComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> BackLightComponent;
protected:
	AStartTile();

	virtual void BeginPlay() override;

public:
	ADoorBase* GetDoor();
	
};
