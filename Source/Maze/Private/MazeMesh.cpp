// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeMesh.h"

// Sets default values
AMazeMesh::AMazeMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMazeMesh::Generate(const int32& Seed, const FIntPoint& InSize, TSet<FIntPoint>& PathTilesRef, TSet<FIntPoint>& EndTilesRef)
{
	this->RandomStream->Initialize(Seed);
	this->Size = InSize;
	this->PathTilesOut = PathTilesRef;
	this->EndTilesOut = EndTilesRef;

	FIntPoint StartCell = this->GetRandomCell();
	this->VisitedCells.Add(StartCell);

	FIntPoint Neigbour;

	while (this->VisitedCells.Num() < this->Size.X * this->Size.Y)
	{
		RandomWalk();
	}

	PathTilesRef = this->PathTilesOut;
	EndTilesRef = this->EndTilesOut;
}


FIntPoint AMazeMesh::GetRandomUnvisitedCell()
{
	FIntPoint Cell = FIntPoint(0, 0);
	while (Cell == FIntPoint(0, 0) || this->VisitedCells.Contains(Cell))
	{
		Cell = this->GetRandomCell();
	}
	return Cell;
}

FIntPoint AMazeMesh::GetRandomCell()
{
	return FIntPoint(this->RandomStream->RandRange(0, this->Size.X), this->RandomStream->RandRange(0, this->Size.Y));
}

FIntPoint AMazeMesh::GetTileNeigboursLoc(FIntPoint Target, int32 Distance, int32 Index)
{
	switch (Index) {
	case 0:
		return Target + FIntPoint(Distance, 0);
	case 1:
		return Target + FIntPoint(0, Distance);
	case 2:
		return Target + FIntPoint(Distance * -1, 0);
	case 3:
		return Target + FIntPoint(0, Distance * -1);
	}

	return Target;
}

FIntPoint AMazeMesh::GetCellNeigbour(FIntPoint Target, int32 Index)
{
	switch (Index) {
	case 0:
		return Target + FIntPoint(1, 0);
	case 1:
		return Target + FIntPoint(0, 1);
	case 2:
		return Target + FIntPoint(-1, 0);
	case 3:
		return Target + FIntPoint(0, 1 * -1);
	} 

	return Target;
}

TArray<TPair<FIntPoint, FIntPoint>> AMazeMesh::RandomWalk()
{
	FIntPoint StartCell = GetRandomUnvisitedCell();
	FIntPoint CurrentCell = StartCell;
	this->VisitedCells.Add(StartCell);

	FIntPoint CurrentTile = FIntPoint(CurrentCell.X * 2 + 1, CurrentCell.Y * 2 + 1);

	FIntPoint Neigbour;
	int32 NeigbourIndex;

	TArray<TPair<FIntPoint, FIntPoint>> Path;

	while (true)
	{
		NeigbourIndex = this->RandomStream->RandRange(0, 3);
		Neigbour = this->GetCellNeigbour(CurrentCell, NeigbourIndex);

		while (Neigbour.X < 0 || Neigbour.Y < 0 || Neigbour.X > this->Size.X || Neigbour.Y > this->Size.Y) {
			NeigbourIndex++;
			if (NeigbourIndex > 3)
				NeigbourIndex = 0;
			Neigbour = this->GetCellNeigbour(CurrentCell, NeigbourIndex);
		}

		Path.Add(TPair<FIntPoint, FIntPoint>(CurrentCell, Neigbour));


		this->PathTilesOut.Add(CurrentTile);
		this->PathTilesOut.Add(GetTileNeigboursLoc(CurrentTile, 1, NeigbourIndex));
		this->PathTilesOut.Add(GetTileNeigboursLoc(CurrentTile, 2, NeigbourIndex));

		if (this->VisitedCells.Contains(Neigbour)) {
			this->VisitedCells.Add(Neigbour);
			break;
		}


		this->VisitedCells.Add(Neigbour);
		CurrentCell = Neigbour;

		CurrentTile = FIntPoint(CurrentCell.X * 2 + 1, CurrentCell.Y * 2 + 1);
	}

	return Path;
}
