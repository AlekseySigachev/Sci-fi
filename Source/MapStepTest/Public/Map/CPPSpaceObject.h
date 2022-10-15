// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPSpaceObject.generated.h"

class ACPPMapBuilder;
class ACPPOrbitalObject;
class ACPPMainGameMode;

UCLASS()
class MAPSTEPTEST_API ACPPSpaceObject : public AActor
{
	GENERATED_BODY()
//Variables
public:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* CentralObject;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowTop;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowRight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowDown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowLeft;

	int32 PosX;
	int32 PosY;
	int32 Direction;
	float OrbitalSpeed;
	float Time;
	float OrbitalRadius;
	bool bDiscovered;
	bool bInside;
	FString Name;
	UMaterialInterface* OpenMaterial;
	UMaterialInterface* CloseMaterial;
	ACPPMapBuilder* MapBuilder;
	TArray<AActor*> OverlappingActors;
	TArray<ACPPOrbitalObject*> OrbitalObjects;
	TArray<FVector> Positions;
	ACPPMainGameMode* GameMode;

private:

	//Methods
public:	
	virtual void Tick(float DeltaTime) override;

	ACPPSpaceObject();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void AllocateArrow(UStaticMeshComponent *Arrow, UStaticMesh* a_ArrowMesh, //
		UMaterialInstance* a_ArrowMaterial, FVector Scale, FVector Location, FRotator Rotation ) const;
	
private:

};
