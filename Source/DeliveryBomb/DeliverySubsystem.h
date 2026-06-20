
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Delivery/DeliveryDetails.h"
#include "DeliverySubsystem.generated.h"

UCLASS()
class DELIVERYBOMB_API UDeliverySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	public:	//Subsystem
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

	public:	//Deliveries
		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		int32 GenerateDeliveries(int32 Count);

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		bool SetActiveDelivery(int32 DeliveryIndex);
		
		UFUNCTION(BlueprintImplementableEvent, Category = "DeliverySubsystem")
		void ReceiveActiveDeliveryRewards(int32 BombTimerAdded);

		UFUNCTION(BlueprintNativeEvent, Category = "DeliverySubsystem")
		void ActiveDeliveryPickedUp();

		UFUNCTION(BlueprintNativeEvent, Category = "DeliverySubsystem")
		void ActiveDeliveryCompleted();

		UFUNCTION(BlueprintNativeEvent, Category = "DeliverySubsystem")
		void ActiveDeliveryFailed();

		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		void RunDeliveryTimer(float DeltaTime);

		UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
		TArray<FDeliveryDetails> GeneratedDeliveries;

		UPROPERTY(BlueprintReadOnly, Category = "DeliverySubsystem")
		FDeliveryDetails ActiveDelivery;

		UPROPERTY(BlueprintReadonly, Category = "DeliverySubsystem")
		bool bIsDeliveryActive = false;

	private:
		UPROPERTY()
		TArray<ADeliveryPoint*> PickupPoints;
		TArray<ADeliveryPoint*> ValidPickupPoints;

		UPROPERTY()
		TArray<ADeliveryPoint*> DeliveryPoints;
		TArray<ADeliveryPoint*> ValidDeliveryPoints;

		float DeliveryTimer = 300.0f;

		//Function made private to ensure it isn't exposed to blueprints
		UFUNCTION(BlueprintCallable, Category = "DeliverySubsystem")
		bool GenerateDelivery(FDeliveryDetails& OutDeliveryDetails);
	public:
		UFUNCTION(BlueprintPure, Category = "DeliverySubsystem")
		int32 GetPickUpPointCount() const { return PickupPoints.Num(); };

		UFUNCTION(BlueprintPure, Category = "DeliverySubsystem")
		int32 GetDeliveryPointCount() const { return DeliveryPoints.Num(); };
};