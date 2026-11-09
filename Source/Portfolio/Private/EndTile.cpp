// Fill out your copyright notice in the Description page of Project Settings.


#include "EndTile.h"
#include "Components/ChildActorComponent.h"
#include "InteractableSignalActorBase.h"

AEndTile::AEndTile() {
	SignalActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	SignalActorComponent->SetupAttachment(Root);
}

void AEndTile::BeginPlay() {
	Super::BeginPlay();


}

AInteractableSignalActorBase* AEndTile::GetSignalActor() {
	return Cast<AInteractableSignalActorBase>(SignalActorComponent->GetChildActor());
}