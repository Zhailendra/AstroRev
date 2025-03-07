// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StabilizerComponent.h"

// Sets default values for this component's properties
UStabilizerComponent::UStabilizerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UStabilizerComponent::BeginPlay()
{
	Super::BeginPlay();

	Body = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}


// Called every frame
void UStabilizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Body) {
		Body->AddForce(FVector::DotProduct(Body->GetPhysicsLinearVelocity(), Body->GetRightVector()) * -LateralForceReduction * Body->GetRightVector());
	}
}

