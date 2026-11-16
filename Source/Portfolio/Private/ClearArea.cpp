// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearArea.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/RectLightComponent.h"
#include "InGameMode.h"

// Sets default values
AClearArea::AClearArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);

	BackLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("BackLight"));
	BackLightComponent->SetupAttachment(Root);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AClearArea::OnBoxBeginOverlap);
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

void AClearArea::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlapComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	AInGameMode* GM = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->OnGameClear();
	}
}