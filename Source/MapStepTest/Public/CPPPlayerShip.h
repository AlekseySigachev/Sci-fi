

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Map/CPPOrbitalObject.h"
#include "CPPPlayerShip.generated.h"
class ACPPSpaceObject;
UCLASS()
class MAPSTEPTEST_API ACPPPlayerShip : public ACPPOrbitalObject
{
	GENERATED_BODY()

	//Functions
public:	
	ACPPPlayerShip();
	ACPPSpaceObject* CurrentStar;

protected:
private:

	//Variables
public:
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* ShipMesh;
private:

};
