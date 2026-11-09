// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearArea.h"

// Sets default values
AClearArea::AClearArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClearArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClearArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

