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

	TArray<FVector> Positions;
	bool bDiscovered;
	
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

	UPROPERTY(BlueprintReadWrite, DisplayName = "OrbitalSpeed", Category = "Main|Set UP")
	float OrbitalSpeed = 0.1f;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Time", Category = "Main|et UP")
	float Time;
	UPROPERTY(BlueprintReadWrite, DisplayName = "OrbitalRadius", Category = "Main|Set UP")
	float OrbitalRadius = 5.0f;
	UPROPERTY(BlueprintReadWrite, DisplayName = "Is Inside SO", Category = "Main|Set UP")
	bool bInside;
	UPROPERTY(BlueprintReadOnly, DisplayName = "GridStep", Category = "Main|Set UP")
	int32 GridStep = 10;
	UPROPERTY(BlueprintReadWrite, DisplayName = "OpenMaterial", Category = "Main|References")
	UMaterialInterface* OpenMaterial;
	UPROPERTY(BlueprintReadWrite, DisplayName = "CloseMaterial", Category = "Main|References")
	UMaterialInterface* CloseMaterial;
	UPROPERTY(BlueprintReadOnly, DisplayName = "MapBuilder", Category = "Main|References")
	ACPPMapBuilder* MapBuilder;
	UPROPERTY(BlueprintReadOnly, DisplayName = "OverlappingActors", Category = "Main|References")
	TArray<AActor*> OverlappingActors;
	UPROPERTY(BlueprintReadOnly, DisplayName = "OrbitalObjects", Category = "Main|References")
	TArray<ACPPOrbitalObject*> OrbitalObjects;
	UPROPERTY(BlueprintReadOnly, DisplayName = "GameMode", Category = "Main|References")
	ACPPMainGameMode* GameMode;

private:

	UPROPERTY(DisplayName = "Stars Data Table")
	UDataTable* DataTable;

	//Methods
public:
	ACPPSpaceObject();
	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, DisplayName = "On Star Discovered", Category = "Main|Functions")
	void OnDiscovered() const;
	/*UFUNCTION(BlueprintCallable, DisplayName = "Set Default Star Properties", Category = "Main|Functions")*/
	void SetProperties(FStarsStruct* Struct);
	UFUNCTION(BlueprintCallable, DisplayName = "Disable Arrow And Direction", Category = "Main|Functions")
	void DisableArrowAndDirection(int32 DirectionToDisable);
	UFUNCTION(BlueprintCallable, DisplayName = "Enable Arrow And Direction", Category = "Main|Functions")
	void EnableArrowAndDirection(int32 DirectionToEnable);
	UFUNCTION(BlueprintCallable, DisplayName = "Get Star Coords", Category = "Main|Functions", BlueprintPure)
	FVector2D GetCoords() const;
	UFUNCTION(BlueprintCallable, DisplayName = "Get Star Direction List", Category = "Main|Functions", BlueprintPure)
	TArray<int32> GetAllowDirectionList() const;
	UFUNCTION(BlueprintCallable, DisplayName = "Draw", Category = "Main|Functions")
	void Draw();
	UFUNCTION(BlueprintCallable, DisplayName = "Get Grid Step", Category = "Main|Functions", BlueprintPure)
	int32 GetGridStep() { return GridStep; };
	UFUNCTION(BlueprintCallable, DisplayName = "Calculate SpaceObjects Positions On Orbit", Category = "Main|Functions")
	void CalcObjectsPositionsOnOrbit();
	UFUNCTION(BlueprintCallable, DisplayName = "Add SpaceObject To Orbit", Category = "Main|Functions")
	void AddSpaceObjectToOrbit(ACPPOrbitalObject* ObjectToAdd);
	UFUNCTION(BlueprintCallable, DisplayName = "Reallocate SpaceObjects Positions On Orbit", Category = "Main|Functions")
	void ReallocateObjectsOnOrbit();
	UFUNCTION(BlueprintCallable, DisplayName = "Remove SpaceObjects From Orbit", Category = "Main|Functions")
	void RemoveObjectFromOrbit(ACPPOrbitalObject* ObjectToRemove);
	UFUNCTION(BlueprintCallable, DisplayName = "Can Go Inside", Category = "Main|Functions", BlueprintPure)
	bool CanGoInside() { return bInside; };
	UFUNCTION(BlueprintCallable, DisplayName = "Reallocate SpaceObjects Positions On Orbit", Category = "Main|Functions")
	void DiscoverStar();

	UFUNCTION(BlueprintCallable, DisplayName = "Event On Click", Category = "Main|Events")
		void OnStarClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

protected:
	virtual void BeginPlay() override;

	void AllocateArrow(UStaticMeshComponent *Arrow, UStaticMesh* a_ArrowMesh, //
		UMaterialInstance* a_ArrowMaterial, FVector Scale, FVector Location, FRotator Rotation ) const;
	//int32 GetGridStep() const;
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
	int32 CalcDirection(int32 CalcDirection) const;
	void EnableDirection(int32 direction);
	void DisableDirection(int32 direction);
	void DrawArrows() const;



private:

};

