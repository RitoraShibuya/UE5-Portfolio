// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
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
	Road,
	TRoad,
	XRoad,
	Room
};

USTRUCT()
struct FTileData
{
	GENERATED_BODY()

public:
	ETileDirectionType Type = ETileDirectionType::Up;

	UPROPERTY(EditAnywhere, Category = "Protfolio",meta = (MakeEditWidget = true));
	FVector Pos;
};

USTRUCT()
struct FGenerateData
{
	GENERATED_BODY()

public:
	FRotator Rotation = FRotator(0.0f,0.0f,0.0f);
	FVector Pos = FVector(0.0f, 0.0f, 0.0f);
};

struct FMapArrayInfo {
	FVector2D Pos;
	ETileType Type;
	ETileDirectionType Direction;
};

//class PORTFOLIO_API EnumInfo
//{
//public:
//	EnumInfo();
//	~EnumInfo();
//};
