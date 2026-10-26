// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSignalActorBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractableSignalActorBase::AInteractableSignalActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableSignalActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableSignalActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractableSignalActorBase::CanInteract() {
	return State == SwitchState::Off;
}
