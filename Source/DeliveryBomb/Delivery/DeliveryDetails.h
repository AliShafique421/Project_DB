// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeliveryPoint.h"
#include "DeliveryDetails.generated.h"

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
		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void SetDeliveryStatus(EDeliveryStatus NewStatus);
};

UENUM(BlueprintType)
enum class EDeliveryStatus
{
	None,
	Pickup,
	InProgress,
	Completed
};
