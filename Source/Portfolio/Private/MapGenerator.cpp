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
	GenerateMapArray();
	GenerateMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GenerateMapArray() {
	TArray<FVector2D> Poses = {
		FVector2D(0,1),
		FVector2D(0,-1),
		FVector2D(-1,0),
		FVector2D(1,0)
	};

	TArray<ETileType> TileTypes{
		ETileType::Road,
		ETileType::TRoad,
		ETileType::XRoad,
		ETileType::Room,
	};

	FVector2D CurrentPos = FVector2D(0, 0);
	ETileType CurrentType = ETileType::Road;
	ETileDirectionType CurrentDirection = ETileDirectionType::Up;
	FMapArrayInfo Next;

	//MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));

	for (int i = 0; i < 100; i++)
	{
		TArray<ETileDirectionType> Candidate = GetCandidate(CurrentPos, CurrentDirection);
		FNextInfo NextCandidate = GetNextCandidate(CurrentPos, CurrentDirection);

		int32 NextCandidateNum = -1;
		if (!NextCandidate.Directions.IsEmpty()) {
			NextCandidateNum = FMath::RandRange(0, NextCandidate.Directions.Num() - 1);
		}
		else {
			if (!NextMapInfo.IsEmpty()) {
				Next = NextMapInfo.Pop();
				CurrentPos = Next.Pos;
				CurrentType = Next.Type;
				CurrentDirection = Next.Direction;
				continue;
			}
			else {
				break;
			}
		}

		CurrentDirection = Candidate[NextCandidateNum];

		//
		int32 CandidateNum = -1;
		int32 DirectionNum = 0;
		if (!Candidate.IsEmpty()) {
			CandidateNum = Candidate.Num() - 1;
		}
		if (CandidateNum > 0) {
			DirectionNum = FMath::RandRange(0, CandidateNum);
			for (int j = 0; j <= CandidateNum; j++) {
				//NextMapInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
			}
		}
		else if (CandidateNum == 0) {
			DirectionNum = 0;
		}
		else {
			if (!NextMapInfo.IsEmpty()) {
				Next = NextMapInfo.Pop();
				CurrentPos = Next.Pos;
				CurrentType = Next.Type;
				CurrentDirection = Next.Direction;
				continue;
			}
			else {
				break;
			}
		}

		MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
		CurrentDirection = Candidate[DirectionNum];
		//

		FVector2D NextVec;
		for (int j = 0; j <= CandidateNum; j++)
		{
			switch (CurrentDirection)
			{
			case ETileDirectionType::Up:
				NextVec = Poses[0];
				break;
			case ETileDirectionType::Down:
				NextVec = Poses[1];
				break;
			case ETileDirectionType::Left:
				NextVec = Poses[2];
				break;
			case ETileDirectionType::Right:
				NextVec = Poses[3];
				break;
			default:
				break;
			}
		}
		CurrentPos += NextVec;
	}

}

FNextInfo AMapGenerator::GetNextCandidate(FVector2D Pos, ETileDirectionType Direction) {
	FNextInfo Nexts;

	TArray<ETileDirectionType> Directions = GetCandidate(Pos, Direction);
	TArray<ETileType> Types = { ETileType::Room };

	int32 CandidateNum = 0;
	int32 DirectionNum = 0;
	if (!Directions.IsEmpty()) {
		CandidateNum = Directions.Num();
	}

	if (CandidateNum >= 3) {
		Types.Add(ETileType::XRoad);
	}
	else if (CandidateNum == 2) {
		for (const ETileDirectionType& Dir : Directions)
		{
			bool CanStreet = false;
			if (Dir == Direction) {
				CanStreet = true;
			}

			if (CanStreet) {
				Types.Add(ETileType::Road);
			}
			else {
				Types.Add(ETileType::TRoad);
			}
		}
	}
	else if (CandidateNum == 1) {
		if (Directions[0] == Direction) {
			Types.Add(ETileType::Road);
		}
	}

	Nexts.Types = Types;
	Nexts.Directions = Directions;

	return Nexts;
}

TArray<ETileDirectionType> AMapGenerator::GetCandidate(FVector2D Pos, ETileDirectionType Direction) {

	TArray<ETileDirectionType> Excluded;

	TArray<FVector2D> NextVecs = {
	FVector2D(0,1),
	FVector2D(0,-1),
	FVector2D(-1,0),
	FVector2D(1,0)
	};

	TArray<ETileDirectionType> Directions = {
		ETileDirectionType::Up,
		ETileDirectionType::Down,
		ETileDirectionType::Left,
		ETileDirectionType::Right
	};

	for (int i = 0; i < 4; i++)
	{
		for (const FMapArrayInfo& Info : MapArrayInfo) {
			if (Info.Pos == Pos + NextVecs[i]) {
				Excluded.Add(Directions[i]);
			}
		}
		for (const FMapArrayInfo& Info : NextMapInfo) {
			if (Info.Pos == Pos + NextVecs[i]) {
				Excluded.Add(Directions[i]);
			}
		}
	}

	TArray<ETileDirectionType> Candinate = {
		ETileDirectionType::Up,
		ETileDirectionType::Down,
		ETileDirectionType::Left,
		ETileDirectionType::Right
	};

	Candinate.RemoveAll([&](ETileDirectionType Dir) {
		return Excluded.Contains(Dir);
		});

	return Candinate;
}

void AMapGenerator::GenerateMap() {
	for (const FMapArrayInfo& Info : MapArrayInfo)
	{
		FVector CurrentPos = FVector(Info.Pos.Y * 1000, Info.Pos.X * 1000, 0.0);
		TSubclassOf<ATileBase> Subclass;
		switch (Info.Type)
		{
		default:
			break;
		case ETileType::Road:
			Subclass = RoadTile;
			break;
		case ETileType::TRoad:
			Subclass = TRoadTile;
			break;
		case ETileType::XRoad:
			Subclass = XRoadTile;
			break;
		case ETileType::Room:
			Subclass = RoomTile;
			break;
		}

		FRotator CurrentRotation = FRotator(0.0, 0.0, 0.0);
		switch (Info.Direction)
		{
		default:
			break;
		case ETileDirectionType::Up:
			break;
		case ETileDirectionType::Down:
			CurrentRotation.Yaw = 180.0f;
			break;
		case ETileDirectionType::Left:
			CurrentRotation.Yaw = -90.0f;
			break;
		case ETileDirectionType::Right:
			CurrentRotation.Yaw = 90.0f;
			break;
		}

		ATileBase* GenerateTile = GetWorld()->SpawnActor<ATileBase>(Subclass);
		GenerateTile->SetActorLocation(CurrentPos);
		GenerateTile->AddActorWorldRotation(CurrentRotation);
	}

	//初期変数宣言
	//int32 MaxNum = Tiles.Num() - 1;
	//FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);

	////次回タイル抽選
	//int32 TileTypeIndex = FMath::RandRange(0, MaxNum);
	//ATileBase* Tile = StartTile->GetDefaultObject<ATileBase>();

	////生成
	//ATileBase* GenerateTile = GetWorld()->SpawnActor<ATileBase>(StartTile);

	////配置
	//GenerateTile->SetActorLocation(CurrentLocation);

	////次回接続地点抽選
	//int32 Num = Tile->GetTileDataArraySize() - 1;
	//int32 NextTilePosIndex = FMath::RandRange(0, Num);
	//FTileData NextTileData = Tile->GetTileData(NextTilePosIndex);

	////次回用回転
	//FVector NextLocation = NextTileData.Pos;

	////次回接続地点更新
	//CurrentLocation += GenerateTile->GetActorLocation() + NextLocation;

	////回転計算
	//FRotator NextRotation = FRotator(0.0, 0.0, 0.0);
	//switch (NextTileData.Type)
	//{
	//default:
	//	break;
	//case ETileDirectionType::Up:
	//	break;
	//case ETileDirectionType::Down:
	//	NextRotation.Yaw = 180.0f;
	//	break;
	//case ETileDirectionType::Left:
	//	NextRotation.Yaw = 270.0f;
	//	break;
	//case ETileDirectionType::Right:
	//	NextRotation.Yaw = 90.0f;
	//	break;
	//}


	//GenerateTile->SetActorRotation(NextRotation);

	//for (int32 i = 0; i < 200; i++)
	//{
	//	TileTypeIndex = FMath::RandRange(0, MaxNum);
	//	Tile = Tiles[TileTypeIndex]->GetDefaultObject<ATileBase>();

	//	Num = Tile->GetTileDataArraySize() - 1;
	//	NextTilePosIndex = FMath::RandRange(0, Num);
	//	NextTileData = Tile->GetTileData(NextTilePosIndex);

	//	FTileData JointLocation = Tile->GetJointData();

	//	switch (JointLocation.Type)
	//	{
	//	default:
	//		break;
	//	case ETileDirectionType::Up:
	//		break;
	//	case ETileDirectionType::Down:
	//		NextRotation.Yaw = 180.0f;
	//		break;
	//	case ETileDirectionType::Left:
	//		NextRotation.Yaw = 270.0f;
	//		break;
	//	case ETileDirectionType::Right:
	//		NextRotation.Yaw = 90.0f;
	//		break;
	//	}

	//	GenerateTile = GetWorld()->SpawnActor<ATileBase>(Tiles[TileTypeIndex]);
	//	GenerateTile->SetActorRotation(NextRotation);

	//	NextLocation = NextTileData.Pos;
	//	CurrentLocation += CurrentLocation + NextLocation;


	//	NextRotation = FRotator(0.0, 0.0, 0.0);
	//	switch (NextTileData.Type)
	//	{
	//	default:
	//		break;
	//	case ETileDirectionType::Up:
	//		break;
	//	case ETileDirectionType::Down:
	//		NextRotation.Yaw = 180.0f;
	//		break;
	//	case ETileDirectionType::Left:
	//		NextRotation.Yaw = 270.0f;
	//		break;
	//	case ETileDirectionType::Right:
	//		NextRotation.Yaw = 90.0f;
	//		break;
	//	}

	//}
}
