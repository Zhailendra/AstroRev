// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCar.generated.h"

struct FInputActionValue;
class UBoxComponent;
class UHoverComponent;
class UDownForceComponent;
class UStabilizerComponent;

UCLASS()
class ASTROREV_API ABaseCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetMaxSpeed();
	float GetAdhesionScale();
	float GetAdhesionMaxForce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Thrust(const FInputActionValue& Value);
	void Steer(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BaseCollider;

	float InputThrust = 0.0f;
	float InputSteer = 0.0f;

private:

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UDownForceComponent* DownForceComponent;

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStabilizerComponent* StabilizerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UHoverComponent* FrontLeftWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UHoverComponent* FrontRightWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UHoverComponent* BackLeftWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UHoverComponent* BackRightWheel;

	UPROPERTY(EditAnywhere, Category = "Player Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Torque = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Player Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Steering = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Player Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Player Movement", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxSteer = 100.0f;

	float AdhesionScale = 1000.0f;

	float AdhesionMaxForce = 10.0f;
};
