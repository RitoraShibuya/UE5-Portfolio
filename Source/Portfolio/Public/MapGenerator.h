// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.h"
#include "MapGenerator.generated.h"

class ATileBase;

UCLASS()
class PORTFOLIO_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateMapArray();

	void GenerateMap();

	TArray<ETileDirectionType> GetCandidate(FVector2D Pos, ETileDirectionType Direction);

	FNextInfo GetNextCandidate(FVector2D Pos, ETileDirectionType Direction);
private:
	TArray<FMapArrayInfo> MapArrayInfo;
	TArray<FMapArrayInfo> NextMapInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> StartTile;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> EndTile;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> RoadTile;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> TRoadTile;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> XRoadTile;

	UPROPERTY(EditDefaultsOnly, Category = "Portfolio")
	TSubclassOf<ATileBase> RoomTile;

	bool IsGoalMaked = false;
};
