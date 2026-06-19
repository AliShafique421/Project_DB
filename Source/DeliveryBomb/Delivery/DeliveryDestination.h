// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delivery/DeliveryPoint.h"
#include "DeliveryDestination.generated.h"

UCLASS()
class DELIVERYBOMB_API ADeliveryDestination : public ADeliveryPoint
{
	GENERATED_BODY()

	public:
		virtual void OnPlayerReached_Implementation(AActor* PlayerActor) override;

	protected:
		virtual void BeginPlay() override;
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
