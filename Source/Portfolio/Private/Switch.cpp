// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Math/Color.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	//OverlayMaterial = Mesh->GetOverlayMaterial();
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	DynamicInstance = UMaterialInstanceDynamic::Create(OverlayMaterial, this);
	Mesh->SetOverlayMaterial(DynamicInstance);
	DynamicInstance->SetVectorParameterValue(
		FName(ParamName),
		OffColor
	);
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
	const FHitResult& SweepResult
) 
{
	if (Gimmick && State == SwitchState::Off) 
	{
		State = SwitchState::On;
		Mesh->SetOverlayMaterial(DynamicInstance);
		DynamicInstance->SetVectorParameterValue(
			FName(ParamName),
			OnColor
		);
		if (IInteractInterface* Interface = Cast<IInteractInterface>(Gimmick)) {
			Interface->OnInteract(OtherActor);
		}
	}
}