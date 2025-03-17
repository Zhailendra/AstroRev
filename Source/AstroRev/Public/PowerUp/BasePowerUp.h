#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePowerUp.generated.h"

class UBoxComponent;

UCLASS()
class ASTROREV_API ABasePowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePowerUp();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Component", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMeshComponent;

};
