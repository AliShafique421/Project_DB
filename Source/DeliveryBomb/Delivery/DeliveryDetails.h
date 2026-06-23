// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeliveryPoint.h"
#include "DeliveryDetails.generated.h"

UENUM(BlueprintType)
enum class EDeliveryStatus : uint8
{
	None,
	Pickup,
	InProgress,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FDeliveryDetails
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
	ADeliveryPoint* PickupPoint = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
	ADeliveryPoint* DeliveryPoint = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
	EDeliveryStatus DeliveryStatus = EDeliveryStatus::None;

	public:
		void SetDeliveryStatus(EDeliveryStatus NewStatus);

		UPROPERTY(BlueprintReadOnly, Category = "Delivery Details")
		float TimeAddedOnAccept = 0.0f;

		UPROPERTY(BlueprintReadOnly, Category = "Delivery Details")
		float TimeAddedOnDelivered = 0.0f;

		UPROPERTY(BlueprintReadOnly, Category = "Delivery Details")
		int32 MoneyRewardOnCompletion = 0.0f;
};