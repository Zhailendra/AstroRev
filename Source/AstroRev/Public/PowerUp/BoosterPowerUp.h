#pragma once

#include "CoreMinimal.h"
#include "PowerUp/BasePowerUp.h"
#include "BoosterPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ASTROREV_API ABoosterPowerUp : public ABasePowerUp
{
	GENERATED_BODY()

public:
	ABoosterPowerUp();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	UPROPERTY(EditAnywhere, Category = "PowerUp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BoostAmount = 5.0f;
};
