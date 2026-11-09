// Fill out your copyright notice in the Description page of Project Settings.


#include "StartTile.h"
#include "Components/ChildActorComponent.h"
#include "DoorBase.h"
#include "Components/RectLightComponent.h"

AStartTile::AStartTile() {
	DoorActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	DoorActorComponent->SetupAttachment(Root);

	LightActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Light"));
	LightActorComponent->SetupAttachment(Root);

	PickupActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("PickupActor"));
	PickupActorComponent->SetupAttachment(Root);

	ClearAreaActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ClearAreaActor"));
	ClearAreaActorComponent->SetupAttachment(Root);

	BackLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("BackLight"));
	BackLightComponent->SetupAttachment(Root);


}

void AStartTile::BeginPlay() {

}

ADoorBase* AStartTile::GetDoor() {
	return Cast<ADoorBase>(DoorActorComponent->GetChildActor());
}