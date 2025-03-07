// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BaseCar.h"
#include "Components/HoverComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DownForceComponent.h"
#include "Components/StabilizerComponent.h"
#include "InputActionValue.h"

// Sets default values
ABaseCar::ABaseCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollider"));
	RootComponent = BaseCollider;

	DownForceComponent = CreateDefaultSubobject<UDownForceComponent>(TEXT("DownForceComponent"));

	StabilizerComponent = CreateDefaultSubobject<UStabilizerComponent>(TEXT("StabilizerComponent"));

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

	GEngine->ClearOnScreenDebugMessages();

	FVector Velocity = BaseCollider->GetComponentVelocity();
	FVector CurrentAngularVelocity = BaseCollider->GetPhysicsAngularVelocityInDegrees();

	float ForwardSpeed = FVector::DotProduct(Velocity, BaseCollider->GetForwardVector());
	float SteerSpeed = FVector::DotProduct(CurrentAngularVelocity, BaseCollider->GetUpVector());

	float Mass = BaseCollider->GetMass() * DeltaTime * 1000;

	if (InputThrust != 0) {
		if (FMath::Abs(ForwardSpeed) < MaxSpeed) {
			BaseCollider->AddForce(BaseCollider->GetForwardVector() * Torque * InputThrust * Mass);
		}
	}
	else {
		BaseCollider->AddForce(-Velocity.GetSafeNormal() * Torque * Mass);
	}

	if (InputSteer != 0) {
		if (FMath::Abs(SteerSpeed) < MaxSteer) {
			BaseCollider->AddTorqueInDegrees(BaseCollider->GetUpVector() * Steering * 1000.0 * InputSteer * Mass);
		}
	}
	else {
		BaseCollider->AddTorqueInDegrees(-BaseCollider->GetUpVector() * SteerSpeed * Steering * 10 * Mass);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Thrust: %f"), ForwardSpeed));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Steer: %f"), SteerSpeed));
}

// Called to bind functionality to input
void ABaseCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCar::Thrust(const FInputActionValue& Value) {
	InputThrust = Value.Get<float>();
}

void ABaseCar::Steer(const FInputActionValue& Value) {
	InputSteer = Value.Get<float>();
}