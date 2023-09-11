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

