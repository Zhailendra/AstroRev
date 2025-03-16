// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BaseCar.h"
#include "Components/TimelineComponent.h"
#include "PlayerCar.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class ASTROREV_API APlayerCar : public ABaseCar
{
	GENERATED_BODY()

public:
	APlayerCar();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ApplyBoost(float Value) const;
	void ApplyZeroGravityDrag() const;

	bool GetIsInZeroGravity() const { return bIsInZeroGravity; }
	void SetIsInZeroGravity(bool Value) { bIsInZeroGravity = Value; }

	UFUNCTION(BlueprintCallable)
	void SetCheckPoint(AActor* LastCheckPoint) { this->CheckPoint = LastCheckPoint; }

	UFUNCTION(BlueprintCallable)
	AActor* GetCheckPoint() const { return this->CheckPoint; }

	UFUNCTION(BlueprintCallable)
	FVector GetBaseLocation() const { return BaseLocation; }

protected:

	void AddPostProcessEffect();

	UFUNCTION()
	void TimelineUpdate(float Value) const;

	void ReverseTimeline();

	void OnTrustTriggered(const FInputActionValue& Value);
	void OnThrustCompleted(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Player Input")
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Player Input")
	UInputAction* ThrustAction;

	UPROPERTY(EditAnywhere, Category = "Player Input")
	UInputAction* SteerAction;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInstance* InstanceMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* PostProcessMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialParameterCollection* MaterialParameterCollection;

	UPROPERTY(EditAnywhere, Category = "TimeLine")
	FTimeline SpeedEffectTimeLine;

	UPROPERTY(EditAnywhere, Category = "TimeLine")
	UCurveFloat* SpeedCurveFloat;

	bool bIsInZeroGravity = false;

	UPROPERTY(EditAnywhere, Category = "GravityDragForce")
	float MaxDragForce = 22000.0f;

	UPROPERTY(EditAnywhere, Category = "GravityDragForce")
	float DragForceMultiplier = 800.0f;

	UPROPERTY(EditAnywhere, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	AActor* CheckPoint;

	UPROPERTY(EditAnywhere, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	FVector BaseLocation;

};
