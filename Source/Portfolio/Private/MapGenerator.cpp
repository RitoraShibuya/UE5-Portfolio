// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include "Math/RandomStream.h"
#include "TileBase.h"
#include "StartTile.h"
#include "EndTile.h"
#include "InteractableSignalActorBase.h"
#include "DoorBase.h"

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

	FVector2D CurrentPos = FVector2D(0, 0);
	ETileType CurrentType = ETileType::Start;
	ETileDirectionType CurrentDirection = ETileDirectionType::Up;
	FMapArrayInfo Next;

	MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
	CurrentPos += Poses[0];

	for (int i = 0; i < 5; i++)
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
			int32 TypeNum = -1;
			if (NextTypeNum > 1) {
				TypeNum = FMath::RandRange(0, NextTypeNum - 1);
			}
			else {
				TypeNum = 0;
			}
			CurrentType = NextCandidate.Types[TypeNum];
		}
		else {
			CurrentType = ETileType::Room;
		}

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
		case ETileType::Start:
		case ETileType::End:
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

	CurrentType = ETileType::End;
	MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));

	while (!NextMapInfo.IsEmpty()) {
		Next = NextMapInfo.Pop();
		CurrentPos = Next.Pos;
		CurrentType = ETileType::Room;
		CurrentDirection = Next.Direction;
		MapArrayInfo.Add(FMapArrayInfo(CurrentPos, CurrentType, CurrentDirection));
	}
}

FNextInfo AMapGenerator::GetNextCandidate(FVector2D Pos, ETileDirectionType Direction) {
	FNextInfo Nexts;

	TArray<ETileDirectionType> Directions = GetCandidate(Pos, Direction);
	TArray<ETileType> Types;

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
	else {
		Types.Add(ETileType::Road);
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
	AStartTile* Start = nullptr;
	AEndTile* End = nullptr;
	for (const FMapArrayInfo& Info : MapArrayInfo)
	{
		FVector CurrentPos = FVector(Info.Pos.Y * 2000, Info.Pos.X * 2000, 0.0);
		TSubclassOf<ATileBase> Subclass;
		switch (Info.Type)
		{
		default:
			break;
		case ETileType::Start:
			Subclass = StartTile;
			break;
		case ETileType::End:
			Subclass = EndTile;
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

		if (Info.Type == ETileType::Start) {
			Start = Cast<AStartTile>(GenerateTile);
		}
		else if (Info.Type == ETileType::End) {
			End = Cast<AEndTile>(GenerateTile);
		}
	}

	if (Start&&End) {
		End->GetSignalActor()->AddGimmick(Start->GetDoor());
	}

}
