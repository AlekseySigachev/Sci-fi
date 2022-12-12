// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPSpaceObject.h"
#include "GameFramework/Actor.h"
#include "MapStepTest/CustomStructs.h"
#include "CPPMapBuilder.generated.h"

UCLASS()
class MAPSTEPTEST_API ACPPMapBuilder : public AActor
{
	GENERATED_BODY()
	
	// Variables
public:
	
protected:
private:
	TMap<FVector2d, ACPPSpaceObject*> MaseDict;
	TArray<ACPPSpaceObject*> DiscoveryHistory;
	
	//Methods
	
public:	
	ACPPMapBuilder();
	virtual void Tick(float DeltaTime) override;
	void AddStartStation(int32 Direction, int32 PosX, int32 PosY, FName Name);
	FStarsStruct* PopRandomStar();
	void DiscoverStar(FVector2d key);
	virtual void BeginPlay() override;
	void AddKeyAndHistory(ACPPSpaceObject* Object, FVector2d Key);
	void CreateUndiscoveredStars(TArray<int32> AllowDirectionList, FVector2d Coords);
	void DeleteUndiscoveredStars(TArray<ACPPSpaceObject*> Stars);
	void CleanUnusedArrows();
	FVector2d CalcNewDelta(int32 Direction);
	bool IsEmpty(TArray<FName> Array);

protected:


private:
	UPROPERTY()
	UDataTable* DataTable;
	TArray<FName> StarsName;
	void Finished();
};
