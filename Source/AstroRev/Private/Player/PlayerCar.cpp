// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerCar::APlayerCar()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APlayerCar::BeginPlay() {
	Super::BeginPlay();

	if (const auto PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
		}
	}
}

void APlayerCar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ThrustAction)
		{
			EnhancedInputComponent->BindAction(ThrustAction, ETriggerEvent::Triggered, this, &APlayerCar::Thrust);
			EnhancedInputComponent->BindAction(ThrustAction, ETriggerEvent::Completed, this, &APlayerCar::Thrust);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("THRUST ENABLED"));
		}
		if (SteerAction)
		{
			EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Started, this, &APlayerCar::Steer);
			EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Completed, this, &APlayerCar::Steer);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("INPUT"));
}