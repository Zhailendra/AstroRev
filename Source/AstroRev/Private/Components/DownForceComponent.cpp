// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DownForceComponent.h"
#include "Pawns/BaseCar.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UDownForceComponent::UDownForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDownForceComponent::BeginPlay()
{
	Super::BeginPlay();

	Body = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	BaseCar = Cast<ABaseCar>(GetOwner());
}


// Called every frame
void UDownForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	double StartTime = FPlatformTime::Seconds();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	double EndTime = FPlatformTime::Seconds();
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Tick Time: %f ms"), (EndTime - StartTime) * 1000));

	if (Body != nullptr && BaseCar != nullptr) {
		// Raycasting to the bottom of the car
		FVector StartPos = Body->GetComponentLocation();
		FVector EndPos = Body->GetComponentLocation() - (Body->GetUpVector() * 400);
		FHitResult HitResult;

		float Angle = FMath::Acos(FVector::DotProduct(Body->GetUpVector(), FVector::UpVector)) * (180.f / PI);

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());

		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			StartPos,
			EndPos,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForOneFrame,
			HitResult,
			false
		);

		//if (DebugLineTrace) {
		//DrawDebugLine(GetWorld(), StartPos, EndPos, bHit ? FColor::Green : FColor::Red, false, DeltaTime, 0, 1.0f);
		//};

		// Setting variables to compute physics

		FVector Velocity = Body->GetPhysicsLinearVelocity();
		float DownForce = Body->GetMass() * GetWorld()->GetGravityZ();

		float Speed = Velocity.Size();
		float VerticalSpeed = FVector::DotProduct(Velocity, HitResult.ImpactNormal);

		float AdhesionFactor = FMath::Clamp(Speed / BaseCar->GetAdhesionScale(), 1.0f, BaseCar->GetAdhesionMaxForce());
		float AdjustedDownForce = DownForce * AdhesionFactor;

		if (bHit) {
			CurrentGravityFactor = FMath::FInterpTo(CurrentGravityFactor, SurfaceGravity, DeltaTime, 1.0f);
			FQuat TargetRotation = FQuat::FindBetweenVectors(Body->GetUpVector(), HitResult.ImpactNormal);
			FVector Torque = TargetRotation.GetRotationAxis() * TargetRotation.GetAngle() * DownForce * 1000.0f;

			Body->AddForceAtLocation(HitResult.ImpactNormal * AdjustedDownForce * CurrentGravityFactor * DeltaTime, Body->GetComponentLocation());
			Body->AddTorqueInDegrees(Torque);
		}
		else {
			//FVector CurrentAngularVelocity = Body->GetPhysicsAngularVelocityInDegrees();
			//FVector NewAngularVelocity = FMath::VInterpTo(CurrentAngularVelocity, FVector::ZeroVector, DeltaTime, 3.0f);
			//Body->SetPhysicsAngularVelocityInDegrees(NewAngularVelocity);

			Body->AddForceAtLocation(FVector::UpVector * DownForce * DeltaTime * AirGravity, Body->GetComponentLocation());

			if (Angle > 20)
			{

			}

			FVector CorrectionTorque = FVector::CrossProduct(Body->GetUpVector(), FVector::UpVector) * Body->GetMass() * 500000000.0f;
			FVector DampenedAngularVelocity = FMath::VInterpTo(Body->GetPhysicsAngularVelocityInDegrees(), FVector::ZeroVector, DeltaTime, 2.0f);
			Body->AddTorqueInDegrees(CorrectionTorque);

			Body->SetPhysicsAngularVelocityInDegrees(DampenedAngularVelocity);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Angle: %f"), Angle));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Velocity: %f"), Speed));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hover Adhesion Factor: %f"), AdhesionFactor));
	}
}

