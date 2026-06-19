// Fill out your copyright notice in the Description page of Project Settings.


#include "Delivery/DeliveryPoint.h"
#include "DeliverySubsystem.h"
#include "Kismet/GameplayStatics.h"

ADeliveryPoint::ADeliveryPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(100.0f);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADeliveryPoint::HandleOverlap);
}

void ADeliveryPoint::BeginPlay()
{
	Super::BeginPlay();	
	DisableCollision();

	DeliverySubsystem = GetWorld()->GetSubsystem<UDeliverySubsystem>();
}

void ADeliveryPoint::EnableCollision_Implementation()
{
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ADeliveryPoint::DisableCollision_Implementation()
{
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADeliveryPoint::ActivateDeliveryPoint_Implementation()
{
	bIsActive = true;
	EnableCollision();
}

void ADeliveryPoint::DeactivateDeliveryPoint_Implementation()
{
	bIsActive = false;
	DisableCollision();
}

void ADeliveryPoint::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive)
		return;

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (OtherActor && OtherActor == playerPawn)
		OnPlayerReached(OtherActor);
}

void ADeliveryPoint::OnPlayerReached_Implementation(AActor* PlayerActor)
{
	return;
}