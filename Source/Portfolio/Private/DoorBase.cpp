// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADoorBase::ADoorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

}

void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorBase::OnSignal(AActor* InteractActor) {
	SignalCount += 1;
	if (SignalCount == SignalNeed) {
		Open();
	}
}

void ADoorBase::Open() {
	OpenMesh();
}

void ADoorBase::OpenMesh() {
	Mesh->AddWorldOffset(FVector(0.0, 0.0, UpValue));
}
