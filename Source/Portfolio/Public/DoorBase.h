// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SignalInterface.h"
#include "DoorBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API ADoorBase : public AActor, public ISignalInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Portfolio")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	float UpValue;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	int32 SignalNeed = 1;
private:
	int32 SignalCount = 0;
public:
	// Sets default values for this actor's properties
	ADoorBase();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Open();

	void OpenMesh();

	virtual void OnSignal(AActor* InteractActor);
public:


};
