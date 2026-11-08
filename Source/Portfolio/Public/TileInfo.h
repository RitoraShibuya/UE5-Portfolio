// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileInfo.generated.h"

/**
 * 
 */

UENUM()
enum class ETileDirectionType
{
	Up,
	Down,
	Left,
	Right
};

UENUM()
enum class ETileType
{
	Road = 0,
	TRoad = 1,
	XRoad = 2,
	Room = 3,
	Start = 4,
	End = 5,
};

USTRUCT()
struct FTileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Protfolio");
	ETileDirectionType Type = ETileDirectionType::Up;

	UPROPERTY(EditAnywhere, Category = "Protfolio",meta = (MakeEditWidget = true));
	FVector Pos;
};

struct FMapArrayInfo {
	FVector2D Pos;
	ETileType Type;
	ETileDirectionType Direction;
};


USTRUCT()
struct FNextInfo
{
	GENERATED_BODY()

public:
	TArray<ETileType> Types;
	TArray<ETileDirectionType> Directions;
};

