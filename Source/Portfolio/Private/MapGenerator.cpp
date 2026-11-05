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

	MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
	CurrentPos += Poses[0];

	for (int i = 0; i < 100; i++)
	{
		FNextInfo NextCandidate = GetNextCandidate(CurrentPos, CurrentDirection);

		int32 NextDirectionNum = -1;
		int32 NextTypeNum = -1;
		if (!NextCandidate.Directions.IsEmpty()) {
			NextDirectionNum = NextCandidate.Directions.Num();
		}
		else {
			CurrentType = ETileType::Room;
			MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
			if (!NextMapInfo.IsEmpty()) {
				Next = NextMapInfo.Pop();
				CurrentPos = Next.Pos;
				CurrentType = Next.Type;
				CurrentDirection = Next.Direction;
				continue;
			}
			else {
				return;
			}
		}

		if (!NextCandidate.Types.IsEmpty()) {
			NextTypeNum = NextCandidate.Types.Num();
			/*for (int j = 0; j < NextTypeNum; j++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Type: %s"), *UEnum::GetValueAsString(NextCandidate.Types[j]));
			}*/
		}

		int32 TypeNum = FMath::RandRange(0, NextTypeNum - 1);
		CurrentType = NextCandidate.Types[TypeNum];

		MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));

		FVector2D Vec;
		switch (CurrentType)
		{
		case ETileType::Road:
			break;
		case ETileType::TRoad:
			NextCandidate.Directions.Remove(CurrentDirection);
			CurrentDirection = NextCandidate.Directions[FMath::RandRange(0, NextCandidate.Directions.Num() - 1)];
			NextCandidate.Directions.Remove(CurrentDirection);

			if (!NextCandidate.Directions.IsEmpty()) {
				switch (NextCandidate.Directions[0])
				{
				case ETileDirectionType::Up:
					Vec = Poses[0];
					break;
				case ETileDirectionType::Down:
					Vec = Poses[1];
					break;
				case ETileDirectionType::Left:
					Vec = Poses[2];
					break;
				case ETileDirectionType::Right:
					Vec = Poses[3];
					break;
				default:
					break;
				}
				NextMapInfo.Add(FMapArrayInfo(CurrentPos + Vec, CurrentType, NextCandidate.Directions[0]));
			}
			else {

			}
			break;
		case ETileType::XRoad:
			CurrentDirection = NextCandidate.Directions[FMath::RandRange(0, NextCandidate.Directions.Num() - 1)];
			NextCandidate.Directions.Remove(CurrentDirection);
			for (int32 j = 0; j < NextCandidate.Directions.Num(); j++)
			{
				switch (NextCandidate.Directions[j])
				{
				case ETileDirectionType::Up:
					Vec = Poses[0];
					break;
				case ETileDirectionType::Down:
					Vec = Poses[1];
					break;
				case ETileDirectionType::Left:
					Vec = Poses[2];
					break;
				case ETileDirectionType::Right:
					Vec = Poses[3];
					break;
				default:
					break;
				}
				NextMapInfo.Add(FMapArrayInfo(CurrentPos + Vec, CurrentType, NextCandidate.Directions[j]));
			}
			break;
		case ETileType::Room:
			if (!NextMapInfo.IsEmpty()) {
				Next = NextMapInfo.Pop();
				CurrentPos = Next.Pos;
				CurrentType = Next.Type;
				CurrentDirection = Next.Direction;
				continue;
			}
			else {
				return;
			}
			break;
		default:
			break;
		}


		FVector2D NextVec;
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
		Types.Add(ETileType::Road);
		Types.Add(ETileType::TRoad);
	}
	else if (CandidateNum == 2) {
		bool CanStreet = false;
		for (const ETileDirectionType Dir : Directions)
		{
			if (Dir == Direction) {
				CanStreet = true;
			}

		}
		if (CanStreet) {
			Types.Add(ETileType::Road);
		}
		else {
			Types.Add(ETileType::TRoad);
		}
	}
	else if (CandidateNum == 1) {
		if (Directions[0] == Direction) {
			Types.Add(ETileType::Road);
		}
	}

	Nexts.Directions = Directions;
	Nexts.Types = Types;

	return Nexts;
}

TArray<ETileDirectionType> AMapGenerator::GetCandidate(FVector2D Pos, ETileDirectionType Direction) {
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

	TArray<ETileDirectionType> Candinate = {
		ETileDirectionType::Up,
		ETileDirectionType::Down,
		ETileDirectionType::Left,
		ETileDirectionType::Right
	};

	for (int i = 0; i < 4; i++)
	{
		for (const FMapArrayInfo Info : MapArrayInfo) {
			if (Info.Pos == Pos + NextVecs[i]) {
				Candinate.Remove(Directions[i]);
			}
		}
		for (const FMapArrayInfo Info : NextMapInfo) {
			if (Info.Pos == Pos + NextVecs[i]) {
				Candinate.Remove(Directions[i]);
			}
		}
	}

	return Candinate;
}

void AMapGenerator::GenerateMap() {
	for (const FMapArrayInfo& Info : MapArrayInfo)
	{
		FVector CurrentPos = FVector(Info.Pos.Y * 3000, Info.Pos.X * 3000, 0.0);
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
