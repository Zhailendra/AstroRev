// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DownForceComponent.generated.h"

class ABaseCar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTROREV_API UDownForceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDownForceComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SurfaceGravity = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AirGravity = 750.0f;

	float CurrentGravityFactor = 1.0f;

	UPrimitiveComponent* Body;

	ABaseCar* BaseCar;
};
