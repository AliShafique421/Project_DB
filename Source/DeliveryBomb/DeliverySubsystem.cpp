
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

void UDeliverySubsystem::RunDeliveryTimer(float DeltaTime)
{
    if (bIsDeliveryActive && (ActiveDelivery.DeliveryStatus == EDeliveryStatus::Pickup || ActiveDelivery.DeliveryStatus == EDeliveryStatus::InProgress))
    {
        ActiveDelivery.DeliveryTime -= DeltaTime;

        if (ActiveDelivery.DeliveryTime <= 0.0f)
        {
            ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Failed);
            ActiveDelivery.DeliveryTime = 0.0f;

            ActiveDeliveryFailed();
        }
    }
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

int32 UDeliverySubsystem::GenerateDeliveries(int32 Count)
{
    int32 GeneratedCount = 0;

    ValidPickupPoints = PickupPoints;
    ValidDeliveryPoints = DeliveryPoints;

    if (GeneratedDeliveries.Num() > 0)
        GeneratedDeliveries.Empty();

    for (int32 i = 0; i < Count; ++i)
    {
        FDeliveryDetails OutDeliveryDetails;

        if (GenerateDelivery(OutDeliveryDetails)) {
            GeneratedCount++;
            GeneratedDeliveries.Add(OutDeliveryDetails);

            if (ValidPickupPoints.Num() == 0 || ValidDeliveryPoints.Num() == 0)
                break;
        } else {
            break;
        }
    }

    return GeneratedCount;
}

bool UDeliverySubsystem::GenerateDelivery(FDeliveryDetails& OutDeliveryDetails)
{
    if(ValidPickupPoints.Num() == 0 || ValidDeliveryPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No pickup or delivery points registered."));
        return false;
    }
        // Doing random points right now just for testing purposes, will implement distance based selection later

        int32 randomPickupIndex = FMath::RandRange(0, ValidPickupPoints.Num() - 1);
        int32 randomDeliveryIndex = FMath::RandRange(0, ValidDeliveryPoints.Num() - 1);
    
        OutDeliveryDetails.PickupPoint = ValidPickupPoints[randomPickupIndex];
        OutDeliveryDetails.DeliveryPoint = ValidDeliveryPoints[randomDeliveryIndex];
        OutDeliveryDetails.SetDeliveryStatus(EDeliveryStatus::None);
        OutDeliveryDetails.DeliveryTime = DeliveryTimer;
        OutDeliveryDetails.BombTimerAdded = 100.0f;

        ValidPickupPoints.RemoveAt(randomPickupIndex);
        ValidDeliveryPoints.RemoveAt(randomDeliveryIndex);

        return true;
}

bool UDeliverySubsystem::SetActiveDelivery(int32 DeliveryIndex)
{
    if (GeneratedDeliveries.IsValidIndex(DeliveryIndex)) {
        ActiveDelivery = GeneratedDeliveries[DeliveryIndex];
        ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Pickup);

        bIsDeliveryActive = true;
        GeneratedDeliveries.Empty();

        return true;
    }

    return false;
}

void UDeliverySubsystem::ActiveDeliveryPickedUp_Implementation()
{
    if (!bIsDeliveryActive)
        return;

    ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::InProgress);
}

void UDeliverySubsystem::ActiveDeliveryCompleted_Implementation()
{
    if (!bIsDeliveryActive)
        return;

    ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Completed);
    ReceiveActiveDeliveryRewards(ActiveDelivery.BombTimerAdded);
    bIsDeliveryActive = false;
}

void UDeliverySubsystem::ActiveDeliveryFailed_Implementation()
{
    if (!bIsDeliveryActive)
        return;

    ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Failed);
    ActiveDelivery.DeliveryTime = 0.0f;
    bIsDeliveryActive = false;
}