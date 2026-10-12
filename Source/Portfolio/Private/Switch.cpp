// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitch::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitch::Tick(float DeltaTime)
{	Super::Tick(DeltaTime);

}

void ASwitch::OnInteract(AActor* InteractActor) {

}

void ASwitch::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlapComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	if (Gimmick) {
		if (IInteractInterface* ActorCheck = Cast<IInteractInterface>(Gimmick)) {
			ActorCheck->OnInteract(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("Switch"));
		}
	}
}