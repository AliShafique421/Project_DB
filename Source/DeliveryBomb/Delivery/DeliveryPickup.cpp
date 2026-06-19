// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryPickup.h"
#include "DeliverySubsystem.h"

void ADeliveryPickup::BeginPlay()
{
    Super::BeginPlay();
    
    if (DeliverySubsystem)
        DeliverySubsystem->RegisterPickUpPoint(this);
    else
        UE_LOG(LogTemp, Error, TEXT("DeliverySubsystem not found in the world."));
}

void ADeliveryPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (DeliverySubsystem)
        DeliverySubsystem->UnregisterPickUpPoint(this);

    Super::EndPlay(EndPlayReason);
}
