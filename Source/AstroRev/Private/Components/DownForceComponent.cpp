// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DownForceComponent.h"

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
}


// Called every frame
void UDownForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Body != nullptr) {
		FVector StartPos = Body->GetComponentLocation();
		FVector EndPos = Body->GetComponentLocation() - (Body->GetUpVector() * 400);
		FHitResult HitResult;

		float Angle = FMath::Acos(FVector::DotProduct(Body->GetUpVector(), FVector::UpVector)) * (180.f / PI);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartPos,
			EndPos,
			ECC_Visibility,
			FCollisionQueryParams("", false, GetOwner())
		);

		//if (DebugLineTrace) {
		DrawDebugLine(GetWorld(), StartPos, EndPos, bHit ? FColor::Green : FColor::Red, false, DeltaTime, 0, 1.0f);
		//};

		float DownForce = Body->GetMass() * GetWorld()->GetGravityZ();

		if (bHit) {
			Body->AddForceAtLocation(Body->GetUpVector() * DownForce * DeltaTime * 50, Body->GetComponentLocation());
		}
		else {
			Body->AddForceAtLocation(FVector::UpVector * DownForce * DeltaTime * 750, Body->GetComponentLocation());

			if (Angle > 20)
			{
				//Body->AddTorqueInDegrees(Body->GetRightVector() * Body->GetMass() * 300.0f * DeltaTime);
			}

		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Angle: %f"), Angle));
	}
}

