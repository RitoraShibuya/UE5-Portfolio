// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Switch.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPrimitiveComponent;
class AActor;
class UMaterialInterface;
class UDynamicMaterialInstance;
struct FHitResult;
struct FLinearColor;

UENUM()
enum class SwitchState : uint8
{
	Off,
	On
};

UCLASS()
class PORTFOLIO_API ASwitch : public AActor, public IInteractInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

	UPROPERTY()
	TObjectPtr<UBoxComponent> OverlapBox;

	UPROPERTY()
	SwitchState State = SwitchState::Off;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicInstance;

protected:
	UPROPERTY(EditAnywhere, Category = "Portfolio")
	UMaterialInterface* OverlayMaterial;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TObjectPtr<AActor> Gimmick;


	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FLinearColor OffColor;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FLinearColor OnColor;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FName ParamName;

public:
	// Sets default values for this actor's properties
	ASwitch();

	virtual void OnInteract(AActor* InteractActor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
