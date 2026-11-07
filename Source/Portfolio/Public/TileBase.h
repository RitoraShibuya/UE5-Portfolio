// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.h"
#include "TileBase.generated.h"

class ATargetPoint;
class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API ATileBase : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Portfolio")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

public:	
	// Sets default values for this actor's properties
	ATileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTileData GetJointData() {
		return JointPoint;
	};

	int32 GetTileDataArraySize() {
		return Point.Num();
	};

	FTileData GetTileData(int32 index) {
		return Point[index];
	};
private:
	UPROPERTY(EditAnywhere, Category = "Portfolio")
	ETileType Type;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	FTileData JointPoint;

	UPROPERTY(EditAnywhere, Category = "Portfolio")
	TArray<FTileData> Point;
};
