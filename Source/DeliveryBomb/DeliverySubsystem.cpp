//© 2026 Ali Shafique. All Rights Reserved.

#include "DeliverySubsystem.h"
#include "Delivery/DeliveryPickup.h"
#include "Delivery/DeliveryDestination.h"
#include "Delivery/DeliveryDetails.h"
#include "Delivery/DeliveryDifficultyStats.h"
#include "Kismet/GameplayStatics.h"
#include "string"
#include "format"

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

//split
//4 total -> minimum diff = easy, maximum diff = hard
// 50/50 split does not cover all
//**go full random**

int32 UDeliverySubsystem::GenerateDeliveries(int32 Count, EDeliveryDifficulty MinimumDifficulty, EDeliveryDifficulty MaximumDifficulty)
{
    int32 GeneratedCount = 0;

    ValidPickupPoints = PickupPoints;
    ValidDeliveryPoints = DeliveryPoints;

    EDeliveryDifficulty SelectedDifficulty = static_cast<EDeliveryDifficulty>(FMath::RandRange((uint8)MinimumDifficulty, (uint8)MaximumDifficulty));

    if (GeneratedDeliveries.Num() > 0)
        GeneratedDeliveries.Empty();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    for (int32 i = 0; i < Count; ++i)
    {
        FDeliveryDetails OutDeliveryDetails;

        if (GenerateDelivery(OutDeliveryDetails, SelectedDifficulty, PlayerPawn)) {
            GeneratedCount++;
            GeneratedDeliveries.Add(OutDeliveryDetails);

            if (ValidPickupPoints.Num() == 0 || ValidDeliveryPoints.Num() == 0)
                break;
        } else {
            break;
        }
    }

    if (GeneratedCount > 0)
        OnDeliveriesGenerated.Broadcast();

    return GeneratedCount;
}

//orders can share the same pickup points but cant have the same drop off points

bool UDeliverySubsystem::GenerateDelivery(FDeliveryDetails& OutDeliveryDetails, EDeliveryDifficulty Difficulty, APawn* PlayerPawn)
{
    if(ValidPickupPoints.Num() == 0 || ValidDeliveryPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No pickup or delivery points registered."));
        return false;
    }

    const UEnum* EnumPtr = StaticEnum<EDeliveryDifficulty>();
    FString DifficultyString = EnumPtr->GetNameStringByValue((int64)Difficulty);
    
    FDeliveryDifficultyStats* DeliveryDifficultyStats = DeliveryDifficultyTable->FindRow<FDeliveryDifficultyStats>(
        FName(DifficultyString), TEXT("Get Difficulty Values")
    );

    float MinDistPickup = FMath::Square(DeliveryDifficultyStats->PickUpDistanceMin);
    float MaxDistPickup = FMath::Square(DeliveryDifficultyStats->PickUpDistanceMax);

    float MinDistDelivery = FMath::Square(DeliveryDifficultyStats->DeliveryDistanceMin);
    float MaxDistDelivery = FMath::Square(DeliveryDifficultyStats->DeliveryDistanceMax);

    TArray<ADeliveryPoint*> PickUpPointsWithinDist;
    
    for (int i = 0; i < ValidPickupPoints.Num(); i++)
    {
        AActor* Point = Cast<AActor>(ValidPickupPoints[i]);

        float DistSqrd = FVector::DistSquared(Point->GetActorLocation(), PlayerPawn->GetActorLocation());
        float Dist = FVector::Distance(Point->GetActorLocation(), PlayerPawn->GetActorLocation());
        
        UE_LOG(LogTemp, Warning, TEXT("DistSqrd for Pickup Index %d (Name: %s): is %.2f distSqrd away from Player and %.2f normalDist away from player"), i, *ValidPickupPoints[i]->GetActorLabel() ,DistSqrd, Dist);
        UE_LOG(LogTemp, Warning, TEXT("The Minimum Distance is %.2f (%.2f) and the Maximum is %.2f (%.2f)"), DeliveryDifficultyStats->PickUpDistanceMin, MinDistPickup, DeliveryDifficultyStats->PickUpDistanceMax, MaxDistPickup);

        if (DistSqrd >= MinDistPickup && DistSqrd <= MaxDistPickup) {
            PickUpPointsWithinDist.Add(ValidPickupPoints[i]);
        
            UE_LOG(LogTemp, Warning, TEXT("Added this Point to the ValidPickupPoints List"));
        }
    }

    TArray<ADeliveryPoint*> DeliveryPointsWithinDist;

    for (int i = 0; i < ValidDeliveryPoints.Num(); i++)
    {
        AActor* Point = Cast<AActor>(ValidDeliveryPoints[i]);

        float DistSqrd = FVector::DistSquared(Point->GetActorLocation(), PlayerPawn->GetActorLocation());
        float Dist = FVector::Distance(Point->GetActorLocation(), PlayerPawn->GetActorLocation());
        
        UE_LOG(LogTemp, Warning, TEXT("DistSqrd for Delivery Index %d (Name: %s): is %.2f distSqrd away from Player and %.2f normalDist away from player"), i, *ValidDeliveryPoints[i]->GetActorLabel() ,DistSqrd, Dist);
        UE_LOG(LogTemp, Warning, TEXT("The Minimum Distance is %.2f and the Maximum is %.2f"), DeliveryDifficultyStats->DeliveryDistanceMin, DeliveryDifficultyStats->DeliveryDistanceMax);

        if (DistSqrd >= MinDistDelivery && DistSqrd <= MaxDistDelivery) {
            DeliveryPointsWithinDist.Add(ValidDeliveryPoints[i]);
        
            UE_LOG(LogTemp, Warning, TEXT("Added this Point to the ValidPickupPoints List"));
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Found %d Pickup Points within Range and %d Delivery Points within Range"), PickUpPointsWithinDist.Num(), DeliveryPointsWithinDist.Num());

    ADeliveryPoint* SelectedPickUpPoint = PickUpPointsWithinDist[FMath::RandRange(0, PickUpPointsWithinDist.Num()-1)];
    ADeliveryPoint* SelectedDeliveryPoint = DeliveryPointsWithinDist[FMath::RandRange(0, DeliveryPointsWithinDist.Num()-1)];

    if (SelectedPickUpPoint)
        OutDeliveryDetails.PickupPoint = SelectedPickUpPoint;

    if (SelectedDeliveryPoint)
        OutDeliveryDetails.DeliveryPoint = SelectedDeliveryPoint;
    
    OutDeliveryDetails.SetDeliveryStatus(EDeliveryStatus::None);

    float PickUpDistanceSqrd = FVector::DistSquared(PlayerPawn->GetActorLocation(), SelectedPickUpPoint->GetActorLocation());
    float PickUpTimeAlpha = FMath::GetMappedRangeValueClamped(FVector2D(MinDistPickup, MaxDistPickup), FVector2D(0.0f, 1.0f), PickUpDistanceSqrd);
    float PickUpTime = FMath::Lerp(DeliveryDifficultyStats->PickUpTimeMin, DeliveryDifficultyStats->PickUpTimeMax, PickUpTimeAlpha) + DeliveryDifficultyStats->AdditionalPickUpTime;

    float DeliveryDistanceSqrd = FVector::DistSquared(PlayerPawn->GetActorLocation(), SelectedDeliveryPoint->GetActorLocation());    
    float DeliveryTimeAlpha = FMath::GetMappedRangeValueClamped(FVector2D(MinDistDelivery, MaxDistDelivery), FVector2D(0.0f, 1.0f), DeliveryDistanceSqrd);
    float DeliveryTime = FMath::Lerp(DeliveryDifficultyStats->DeliveryTimeMin, DeliveryDifficultyStats->DeliveryTimeMax, DeliveryTimeAlpha) + DeliveryDifficultyStats->AdditionalDeliveryTime;

    OutDeliveryDetails.TimeAddedOnAccept = PickUpTime;
    OutDeliveryDetails.TimeAddedOnDelivered = DeliveryTime;
    OutDeliveryDetails.MoneyRewardOnCompletion = 300;

    // ValidPickupPoints.Remove(SelectedPickUpPoint);
    ValidDeliveryPoints.Remove(SelectedDeliveryPoint);

    return true;
}

bool UDeliverySubsystem::SetActiveDelivery(int32 DeliveryIndex)
{
    if (GeneratedDeliveries.IsValidIndex(DeliveryIndex)) {
        ActiveDelivery = GeneratedDeliveries[DeliveryIndex];
        ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Pickup);

        bIsDeliveryActive = true;

        OnDeliveryStarted.Broadcast();
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
    ReceiveActiveDeliveryRewards();
    bIsDeliveryActive = false;
}

void UDeliverySubsystem::ActiveDeliveryFailed_Implementation()
{
    if (!bIsDeliveryActive)
        return;

    ActiveDelivery.SetDeliveryStatus(EDeliveryStatus::Failed);
    // ActiveDelivery.DeliveryTime = 0.0f;
    bIsDeliveryActive = false;
}