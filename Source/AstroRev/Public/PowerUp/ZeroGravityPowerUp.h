#pragma once

#include "CoreMinimal.h"
#include "PowerUp/BasePowerUp.h"
#include "ZeroGravityPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ASTROREV_API AZeroGravityPowerUp : public ABasePowerUp
{
	GENERATED_BODY()

public:
	AZeroGravityPowerUp();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
