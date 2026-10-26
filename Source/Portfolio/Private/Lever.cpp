// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"
#include "Components/WidgetComponent.h"
#include "SignalInterface.h"

// Sets default values
ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->AttachToComponent(
		RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform
	);

	WidgetComponent->SetVisibility(false);
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALever::OnInteract(AActor* InteractActor) {
	if (State == SwitchState::Off)
	{
		State = SwitchState::On;

		MeshComponent->AddRelativeRotation(FRotator(0.0, 0.0, -180.0).Quaternion());

		for (AActor* Gimmick : Gimmicks) {
			if (ISignalInterface* Interface = Cast<ISignalInterface>(Gimmick)) {
				Interface->OnSignal(InteractActor);
			}
		}
	}
}

void ALever::OnBeginFocus() {
	WidgetComponent->SetVisibility(true);
}

void ALever::OnEndFocus() {
	WidgetComponent->SetVisibility(false);
}
