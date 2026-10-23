// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "PickupInterface.h"
#include "PickupActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API APickupActor : public AActor,public IInteractInterface, public IPickupInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

private:
	TObjectPtr<USceneComponent> Root;

public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UStaticMeshComponent* GetMeshComponent() override;
};
