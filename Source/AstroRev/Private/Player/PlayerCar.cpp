// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Camera/CameraShakeBase.h"
#include "Camera/MyLegacyCameraShake.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollectionInstance.h"

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

	if (SpeedCurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineUpdate"));

		SpeedEffectTimeLine.AddInterpFloat(SpeedCurveFloat, TimelineProgress);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpeedCurveFloat is NOT valid"));
	}

}

void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpeedEffectTimeLine.IsPlaying())
	{
		SpeedEffectTimeLine.TickTimeline(DeltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Timeline is Playing"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Timeline is NOT Playing"));
	}

	float Speed = GetVelocity().Size();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("SPEED: ") + FString::SanitizeFloat(Speed));

	if (Speed < 5500.0f)
	{
		ReverseTimeline();
	}

	if (CameraComponent)
	{
		float NewFOV = FMath::Clamp(FMath::Lerp(80.0f, 100.0f, Speed / MaxSpeed), 80.0f, 100.0f);
		CameraComponent->SetFieldOfView(NewFOV);

		if (Speed > 5000.0f) 
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController)
			{
				PlayerController->ClientStartCameraShake(UMyLegacyCameraShake::StaticClass());
			}
			AddPostProcessEffect();
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
			EnhancedInputComponent->BindAction(ThrustAction, ETriggerEvent::Triggered, this, &APlayerCar::OnTrustTriggered);
			EnhancedInputComponent->BindAction(ThrustAction, ETriggerEvent::Completed, this, &APlayerCar::OnThrustCompleted);
		}
		if (SteerAction)
		{
			EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Started, this, &APlayerCar::Steer);
			EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Completed, this, &APlayerCar::Steer);
		}
	}
}

void APlayerCar::OnTrustTriggered(const FInputActionValue& Value)
{
	SpeedEffectTimeLine.Play();
	Thrust(Value);
}

void APlayerCar::OnThrustCompleted(const FInputActionValue& Value)
{
	Thrust(Value);
}


void APlayerCar::AddPostProcessEffect()
{
	if (CameraComponent && InstanceMaterial)
	{
		PostProcessMaterial = UMaterialInstanceDynamic::Create(InstanceMaterial, this);

		CameraComponent->PostProcessSettings.AddBlendable(PostProcessMaterial, 1.0f);
	}
}

void APlayerCar::TimelineUpdate(float Value) const
{
	if (MaterialParameterCollection)
	{
		UMaterialParameterCollectionInstance* Instance = GetWorld()->GetParameterCollectionInstance(MaterialParameterCollection);
		if (Instance)
		{
			Instance->SetScalarParameterValue("Alpha", Value);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Alpha Value: %f"), Value));
		}
	}

	if (PostProcessMaterial)
	{
		PostProcessMaterial->SetScalarParameterValue("Alpha", Value);
	}
}

void APlayerCar::ReverseTimeline()
{
	SpeedEffectTimeLine.Reverse();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Timeline Reversed"));
}
