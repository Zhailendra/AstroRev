// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverComponent.generated.h"

class ABaseCar;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTROREV_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceBetweenHoverToGround = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Damping = 100000.0f;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Stiffness = 1000000.0f;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool DebugLineTrace = true;

	float HoverForce = 0.0f;

	float PreviousCompression = 0.0f;

	UPrimitiveComponent* Body;

	ABaseCar* BaseCar;
};
