// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
APickupActor::APickupActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);
	MeshComponent->SetSimulatePhysics(true);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	WidgetComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->AttachToComponent(
		MeshComponent,
		FAttachmentTransformRules::KeepRelativeTransform
	);

	WidgetComponent->SetVisibility(false);
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* APickupActor::GetMeshComponent() {
	return MeshComponent;
}

void APickupActor::OnBeginFocus() {
	WidgetComponent->SetVisibility(true);
}

void APickupActor::OnEndFocus() {
	WidgetComponent->SetVisibility(false);
}