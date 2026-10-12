// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Door.generated.h"

class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API ADoor : public AActor, public IInteractInterface
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
	ADoor();

	virtual void OnInteract(AActor* InteractActor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Open();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
