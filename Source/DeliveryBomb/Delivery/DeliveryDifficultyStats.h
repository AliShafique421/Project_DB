// Copyright (c) 2026 Illumen Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Delivery/DeliveryDetails.h"

UENUM(BlueprintType)
enum class EDeliveryDifficulty : uint8
{
	Easy = 0,
	Medium = 1,
	Hard = 2,
	VeryHard = 3,
	Impossible = 4 
};

USTRUCT(BlueprintType)
struct FDeliveryDifficultyStats : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDeliveryDifficulty DeliveryDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PickUpDistanceMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PickUpDistanceMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeliveryDistanceMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeliveryDistanceMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PickUpTimeMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PickUpTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeliveryTimeMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeliveryTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AdditionalPickUpTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AdditionalDeliveryTime;
};
