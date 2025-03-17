#include "PowerUp/ZeroGravityPowerUp.h"

#include "Components/BoxComponent.h"
#include "Player/PlayerCar.h"

AZeroGravityPowerUp::AZeroGravityPowerUp()
{

}

void AZeroGravityPowerUp::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollider)
	{
		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AZeroGravityPowerUp::OnBoxOverlapBegin);
		BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AZeroGravityPowerUp::OnBoxOverlapEnd);
	}
}

void AZeroGravityPowerUp::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Car"))
	{
		APlayerCar* PlayerCar = Cast<APlayerCar>(OtherActor);

		if (PlayerCar)
		{
			PlayerCar->SetIsInZeroGravity(true);
		}
	}
}

void AZeroGravityPowerUp::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Car"))
	{
		APlayerCar* PlayerCar = Cast<APlayerCar>(OtherActor);

		if (PlayerCar)
		{
			PlayerCar->SetIsInZeroGravity(false);
		}
	}
}

