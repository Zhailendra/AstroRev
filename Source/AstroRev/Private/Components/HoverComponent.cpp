// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HoverComponent.h"
#include "Pawns/BaseCar.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	Body = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	BaseCar = Cast<ABaseCar>(GetOwner());
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner() && Body != nullptr && BaseCar != nullptr) {
		FVector StartPos = GetComponentLocation();
		FVector EndPos = GetComponentLocation() - (GetUpVector() * DistanceBetweenHoverToGround);
		FHitResult HitResult;
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartPos,
			EndPos,
			ECC_Visibility,
			FCollisionQueryParams("", false, GetOwner())
		);
		
		if (DebugLineTrace == true) {
			DrawDebugLine(GetWorld(), StartPos, EndPos, bHit ? FColor::Green : FColor::Red, false, DeltaTime, 0, 1.0f);
		};

		FVector Velocity = Body->GetPhysicsLinearVelocity();
		float LandingSpeed = Velocity.Size();
		float DynamicDamping = FMath::Clamp(LandingSpeed / BaseCar->GetAdhesionScale(), 0.1f, 3.0f);

		if (bHit) {
			float Compressor = (DistanceBetweenHoverToGround - HitResult.Distance) / DistanceBetweenHoverToGround;
			HoverForce = (Compressor * Stiffness) + ((Compressor - PreviousCompression) / GetWorld()->GetDeltaSeconds() * Damping);
			PreviousCompression = Compressor;

			HoverForce *= DynamicDamping;
			Body->AddForceAtLocation(GetUpVector() * HoverForce, GetComponentLocation());

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hover Force: %f"), HoverForce));
		}
	}
 }

