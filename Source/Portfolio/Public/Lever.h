// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableSignalActorBase.h"
#include "Lever.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class PORTFOLIO_API ALever : public AInteractableSignalActorBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TObjectPtr<UWidgetComponent> WidgetComponent;

public:
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AActor* InteractActor) override;

	virtual void OnBeginFocus() override;

	virtual void OnEndFocus() override;

};
