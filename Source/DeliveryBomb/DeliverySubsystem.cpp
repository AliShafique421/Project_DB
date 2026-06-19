
#include "DeliverySubsystem.h"
#include "Delivery/DeliveryDetails.h"

void UDeliverySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UDeliverySubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UDeliverySubsystem::RegisterPickUpPoint(ADeliveryPoint* PickupPoint)
{
    if (PickupPoint)
        PickupPoints.AddUnique(PickupPoint);
}

void UDeliverySubsystem::UnregisterPickUpPoint(ADeliveryPoint* PickupPoint)
{
    if (PickupPoint)
        PickupPoints.Remove(PickupPoint);
}

void UDeliverySubsystem::RegisterDeliveryPoint(ADeliveryPoint* DeliveryPoint)
{
    if (DeliveryPoint)
        DeliveryPoints.AddUnique(DeliveryPoint);
}

void UDeliverySubsystem::UnregisterDeliveryPoint(ADeliveryPoint* DeliveryPoint)
{
    if (DeliveryPoint)
        DeliveryPoints.Remove(DeliveryPoint);
}

bool UDeliverySubsystem::GenerateDelivery()
{
    if(PickupPoints.Num() == 0 || DeliveryPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No pickup or delivery points registered."));
        return false;
    }

        // Doing random points right now just for testing purposes, will implement distance based selection later

        int32 randomPickupIndex = FMath::RandRange(0, PickupPoints.Num() - 1);
        int32 randomDeliveryIndex = FMath::RandRange(0, DeliveryPoints.Num() - 1);
    
        deliveryDetails.PickupPoint = PickupPoints[randomPickupIndex];
        deliveryDetails.DeliveryPoint = DeliveryPoints[randomDeliveryIndex];
        
        return true;
}

