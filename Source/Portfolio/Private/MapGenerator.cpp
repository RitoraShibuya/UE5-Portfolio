// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include "Math/RandomStream.h"
#include "TileBase.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GenerateMapArray() {
	int32 MaxNum = Tiles.Num() - 1;
	FVector CurrentLocation = FVector(0.0f,0.0f,0.0f);

	int32 TileTypeIndex = FMath::RandRange(0, MaxNum);
	ATileBase* Tile = StartTile->GetDefaultObject<ATileBase>();

	ATileBase* GenerateTile = GetWorld()->SpawnActor<ATileBase>(StartTile);
	GenerateTile->SetActorLocation(CurrentLocation);

	int32 Num = Tile->GetTileDataArraySize() - 1;
	int32 NextTilePosIndex = FMath::RandRange(0, Num);
	FTileData NextTileData = Tile->GetTileData(NextTilePosIndex);

	FVector NextLocation = NextTileData.Pos;

	CurrentLocation += GenerateTile->GetActorLocation() + NextLocation;

	FRotator NextRotation = FRotator(0.0,0.0,0.0);
	switch (NextTileData.Type)
	{
	default:
		break;
	case ETileDirectionType::Up:
		break;
	case ETileDirectionType::Down:
		NextRotation.Yaw = 180.0f;
		break;
	case ETileDirectionType::Left:
		NextRotation.Yaw = 270.0f;
		break;
	case ETileDirectionType::Right:
		NextRotation.Yaw = 90.0f;
		break;
	}

	GenerateTile->SetActorRotation(NextRotation);

	for (int32 i = 0; i < 200; i++)
	{
		TileTypeIndex = FMath::RandRange(0, MaxNum);
		Tile = Tiles[TileTypeIndex]->GetDefaultObject<ATileBase>();

		Num = Tile->GetTileDataArraySize() - 1;
		NextTilePosIndex = FMath::RandRange(0, Num);
		NextTileData = Tile->GetTileData(NextTilePosIndex);

		FTileData JointLocation = Tile->GetJointData();
		
		switch (JointLocation.Type)
		{
		default:
			break;
		case ETileDirectionType::Up:
			break;
		case ETileDirectionType::Down:
			NextRotation.Yaw = 180.0f;
			break;
		case ETileDirectionType::Left:
			NextRotation.Yaw = 270.0f;
			break;
		case ETileDirectionType::Right:
			NextRotation.Yaw = 90.0f;
			break;
		}

		ATileBase* GenerateTile = GetWorld()->SpawnActor<ATileBase>(Tiles[TileTypeIndex]);
		GenerateTile->SetActorRotation(NextRotation);

		NextLocation = NextTileData.Pos;
		CurrentLocation += CurrentLocation + NextLocation;


		NextRotation = FRotator(0.0, 0.0, 0.0);
		switch (NextTileData.Type)
		{
		default:
			break;
		case ETileDirectionType::Up:
			break;
		case ETileDirectionType::Down:
			NextRotation.Yaw = 180.0f;
			break;
		case ETileDirectionType::Left:
			NextRotation.Yaw = 270.0f;
			break;
		case ETileDirectionType::Right:
			NextRotation.Yaw = 90.0f;
			break;
		}

	}
}

void AMapGenerator::GenerateMap() {

}