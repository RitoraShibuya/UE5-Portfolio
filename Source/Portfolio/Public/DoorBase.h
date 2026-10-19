// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "DoorBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API ADoorBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Portfolio")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	float UpValue;
public:	
	// Sets default values for this actor's properties
	ADoorBase();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Open();

	UFUNCTION()
	virtual void OnInteract(AActor* InteractActor);
public:	
	

};
