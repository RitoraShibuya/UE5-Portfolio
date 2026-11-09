// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InteractableSignalActorBase.generated.h"

UENUM()
enum class SwitchState : uint8
{
	Off,
	On
};

UCLASS()
class PORTFOLIO_API AInteractableSignalActorBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TArray<TObjectPtr<AActor>> Gimmicks;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	SwitchState State = SwitchState::Off;
public:
	// Sets default values for this actor's properties
	AInteractableSignalActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual bool CanInteract() override;

	void AddGimmick(AActor* NewGimmick);

};
