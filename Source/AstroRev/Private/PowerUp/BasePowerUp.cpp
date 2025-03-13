#include "PowerUp/BasePowerUp.h"

#include "Components/BoxComponent.h"

ABasePowerUp::ABasePowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(GetRootComponent());

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetupAttachment(BoxCollider);

}

void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

