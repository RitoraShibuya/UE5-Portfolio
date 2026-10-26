// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractInterface.h"
#include "SignalInterface.h"

// Add default functionality here for any IInteractInterface functions that are not pure virtual.

void IInteractInterface::OnInteract(AActor* InteractActor) {
	
}

bool IInteractInterface::CanInteract() {
	return true;
}

void IInteractInterface::OnBeginFocus() {
	
}

void IInteractInterface::OnEndFocus() {
	
}