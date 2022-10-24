// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "MapStepTest/CustomStructs.h"
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
	UPROPERTY()
	int32 PosX;
	
	UPROPERTY()
	int32 PosY;
	
	UPROPERTY()
	int32 Direction;
	
	UPROPERTY()
	mutable FName Name;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CentralObject;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ArrowTop;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ArrowRight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ArrowDown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ArrowLeft;

	float OrbitalSpeed;
	float Time;
	float OrbitalRadius;
	bool bDiscovered;
	bool bInside;
	UMaterialInterface* OpenMaterial;
	UMaterialInterface* CloseMaterial;
	ACPPMapBuilder* MapBuilder;
	TArray<AActor*> OverlappingActors;
	TArray<ACPPOrbitalObject*> OrbitalObjects;
	TArray<FVector> Positions;
	ACPPMainGameMode* GameMode;

private:
 int32 GridStep = 10;
	UPROPERTY()
	UDataTable* DataTable;

	//Methods
public:
	ACPPSpaceObject();
	
	virtual void Tick(float DeltaTime) override;
	void OnDiscovered() const;
	void SetProperties(FStarsStruct* Struct);
	void DisableArrowAndDirection(int8 direction);
	void EnableArrowAndDirection(int8 direction);
	FVector2d GetCoords() const;
	TArray<int8> GetAllowDirectionList() const;
	void Draw();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void AllocateArrow(UStaticMeshComponent *Arrow, UStaticMesh* a_ArrowMesh, //
		UMaterialInstance* a_ArrowMaterial, FVector Scale, FVector Location, FRotator Rotation ) const;
	int32 GetGridStep() const;
	void EnableArrowTop() const;
	void EnableArrowRight() const;
	void EnableArrowDown() const;
	void EnableArrowLeft() const;
	void DisableArrowTop() const;
	void DisableArrowRight() const;
	void DisableArrowDown() const;
	void DisableArrowLeft() const;
	bool CanMoveTop() const;
	bool CanMoveDown() const;
	bool CanMoveRight() const;
	bool CanMoveLeft() const;
	int8 CalcDirection(int8 CalcDirection) const;
	void EnableDirection(int8 direction);
	void DisableDirection(int8 direction);
	void DrawArrows() const;

private:

};

