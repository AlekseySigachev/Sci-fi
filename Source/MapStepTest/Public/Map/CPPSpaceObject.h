// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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
	UPROPERTY()
	int32 PosX;
	
	UPROPERTY()
	int32 PosY;
	
	UPROPERTY()
	int32 Direction;
	
	UPROPERTY()
	FString Name;
	
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
	void OnDiscovered();
	void SetProperties(FString name, int32 direction, int32 planetquantity, UMaterialInterface* material);
	FVector2d GetCoords() const;
	TArray<int32> GetAllowDirectionList();
	void Draw();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void AllocateArrow(UStaticMeshComponent *Arrow, UStaticMesh* a_ArrowMesh, //
		UMaterialInstance* a_ArrowMaterial, FVector Scale, FVector Location, FRotator Rotation ) const;
	int32 GetGridStep() const;
	void EnableArrowTop();
	void EnableArrowRight();
	void EnableArrowDown();
	void EnableArrowLeft();
	void DisableArrowTop();
	void DisableArrowRight();
	void DisableArrowDown();
	void DisableArrowLeft();
	void DisableArrowAndDirection(int32 direction);
	void EnableArrowAndDirection(int32 direction);
	bool CanMoveTop();
	bool CanMoveDown();
	bool CanMoveRight();
	bool CanMoveLeft();
	int32 CalcDirection(int32 CalcDirection);
	void EnableDirection(int32 direction);
	void DisableDirection(int32 direction);
	void DrawArrows();

private:

};

