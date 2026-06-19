// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "DeliveryPoint.generated.h"

UCLASS()
class DELIVERYBOMB_API ADeliveryPoint : public AActor
{
	GENERATED_BODY()

public:	
	ADeliveryPoint();

	class UDeliverySubsystem* DeliverySubsystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = false;

protected:
	virtual void BeginPlay() override;

	void HandleOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void EnableCollision();

	UFUNCTION(BlueprintNativeEvent)
	void DisableCollision();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateDeliveryPoint();

	UFUNCTION(BlueprintNativeEvent)
	void DeactivateDeliveryPoint();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerReached(AActor* PlayerActor);

};
