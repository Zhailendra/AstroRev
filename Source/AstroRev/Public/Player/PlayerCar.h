// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BaseCar.h"
#include "PlayerCar.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputComponent;

UCLASS()
class ASTROREV_API APlayerCar : public ABaseCar
{
	GENERATED_BODY()

public:
	APlayerCar();

	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
};
