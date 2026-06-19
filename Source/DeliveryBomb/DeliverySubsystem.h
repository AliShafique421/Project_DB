
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Delivery/DeliveryDetails.h"
#include "DeliverySubsystem.generated.h"

UCLASS()
class DELIVERYBOMB_API UDeliverySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	public:
		virtual void Initialize(FSubsystemCollectionBase& Collection) override;
		virtual void Deinitialize() override;
		
		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void RegisterPickUpPoint(ADeliveryPoint* PickupPoint);

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void UnregisterPickUpPoint(ADeliveryPoint* PickupPoint);

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void RegisterDeliveryPoint(ADeliveryPoint* DeliveryPoint);

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void UnregisterDeliveryPoint(ADeliveryPoint* DeliveryPoint);

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		bool GenerateDelivery();

		UFUNCTION(BlueprintPure, Category = "DeliverySubsystem")
		int32 GetPickUpPointCount() const { return PickupPoints.Num(); };

		UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
		FDeliveryDetails deliveryDetails;

	private:
		UPROPERTY()
		TArray<ADeliveryPoint*> PickupPoints;

		UPROPERTY()
		TArray<ADeliveryPoint*> DeliveryPoints;
};