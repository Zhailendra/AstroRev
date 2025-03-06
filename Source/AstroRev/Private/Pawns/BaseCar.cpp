// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BaseCar.h"
#include "Components/HoverComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DownForceComponent.h"

// Sets default values
ABaseCar::ABaseCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollider"));
	RootComponent = BaseCollider;

	DownForceComponent = CreateDefaultSubobject<UDownForceComponent>(TEXT("DownForceComponent"));

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetupAttachment(BaseCollider);

	FrontLeftWheel = CreateDefaultSubobject<UHoverComponent>(TEXT("FrontLeftWheel"));
	FrontLeftWheel->SetupAttachment(BaseCollider);

	FrontRightWheel = CreateDefaultSubobject<UHoverComponent>(TEXT("FrontRightWheel"));
	FrontRightWheel->SetupAttachment(BaseCollider);

	BackLeftWheel = CreateDefaultSubobject<UHoverComponent>(TEXT("BackLeftWheel"));
	BackLeftWheel->SetupAttachment(BaseCollider);

	BackRightWheel = CreateDefaultSubobject<UHoverComponent>(TEXT("BackRightWheel"));
	BackRightWheel->SetupAttachment(BaseCollider);
}

// Called when the game starts or when spawned
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

