// Fill out your copyright notice in the Description page of Project Settings.


#include "Delivery/DeliveryDestination.h"
#include "DeliverySubsystem.h"

void ADeliveryDestination::BeginPlay()
{
    Super::BeginPlay();
    
	if (DeliverySubsystem)
		DeliverySubsystem->RegisterDeliveryPoint(this);
	else
		UE_LOG(LogTemp, Error, TEXT("DeliverySubsystem not found in the world."));
}

void ADeliveryDestination::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (DeliverySubsystem)
        DeliverySubsystem->UnregisterDeliveryPoint(this);

    Super::EndPlay(EndPlayReason);
}

void ADeliveryDestination::OnPlayerReached_Implementation(AActor* PlayerActor)
{
    if (!DeliverySubsystem)
        return;

    DeliverySubsystem->ActiveDeliveryCompleted();
}

