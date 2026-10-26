// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableSignalActorBase.h"
#include "Switch.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPrimitiveComponent;
class AActor;
class UMaterialInterface;
class UDynamicMaterialInstance;
struct FHitResult;
struct FLinearColor;

UCLASS()
class PORTFOLIO_API ASwitch : public AInteractableSignalActorBase
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<UBoxComponent> OverlapBox;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicInstance;

protected:
	UPROPERTY(EditAnywhere, Category = "Portfolio")
	UMaterialInterface* OverlayMaterial;


	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FLinearColor OffColor;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FLinearColor OnColor;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FName ParamName;

public:
	// Sets default values for this actor's properties
	ASwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
