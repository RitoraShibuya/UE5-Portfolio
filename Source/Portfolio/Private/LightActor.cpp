// Fill out your copyright notice in the Description page of Project Settings.


#include "LightActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/RectLightComponent.h"

// Sets default values
ALightActor::ALightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComponent->SetupAttachment(Root);

	LightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("Light"));
	LightComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

