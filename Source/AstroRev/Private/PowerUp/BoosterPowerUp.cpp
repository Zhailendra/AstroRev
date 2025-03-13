#include "PowerUp/BoosterPowerUp.h"

#include "Components/BoxComponent.h"
#include "Player/PlayerCar.h"

ABoosterPowerUp::ABoosterPowerUp()
{
	if (BoxCollider)
	{
		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABoosterPowerUp::OnBoxOverlapBegin);
	}
}

void ABoosterPowerUp::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Car"))
	{
		const APlayerCar* PlayerCar = Cast<APlayerCar>(OtherActor);

		if (PlayerCar)
		{
			PlayerCar->ApplyBoost(BoostAmount);
		}
	}
}