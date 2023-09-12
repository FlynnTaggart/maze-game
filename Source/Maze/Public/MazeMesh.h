// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/IntPoint.h"
#include "Containers/Set.h"
#include "Math/RandomStream.h"
#include "MazeMesh.generated.h"

UCLASS()
class MAZE_API AMazeMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeMesh();
	
	// Generate maze using seed
	UFUNCTION(BlueprintCallable)
	void Generate(const int32& Seed, const FIntPoint& InSize, TSet<FIntPoint>& PathTilesRef, TSet<FIntPoint>& EndTilesRef);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FIntPoint GetRandomUnvisitedCell();
	FIntPoint GetRandomCell();
	FIntPoint GetTileNeigboursLoc(FIntPoint Target, int32 Distance, int32 Index);
	FIntPoint GetCellNeigbour(FIntPoint Target, int32 Index);

	TArray<TPair<FIntPoint, FIntPoint>> RandomWalk();


	TSet<FIntPoint> VisitedCells;

	FRandomStream* RandomStream = new FRandomStream();
	FIntPoint Size = FIntPoint(16, 16);
	TSet<FIntPoint> PathTilesOut;
	TSet<FIntPoint> EndTilesOut;
};
