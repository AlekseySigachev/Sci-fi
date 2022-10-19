// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPSpaceObject.h"
#include "GameFramework/Actor.h"
#include "CPPMapBuilder.generated.h"

UCLASS()
class MAPSTEPTEST_API ACPPMapBuilder : public AActor
{
	GENERATED_BODY()
	// Variables
public:
protected:
private:
	TMap<ACPPSpaceObject*, FString> MaseDict;
	TArray<ACPPSpaceObject*> DiscoveryHistory;
	
	//Methods
public:	
	ACPPMapBuilder();

	virtual void Tick(float DeltaTime) override;
	void AddStartStation(int32 Direction, int32 PosX, int32 PosY, FString Name);

protected:
	virtual void BeginPlay() override;

	FString GenNewKey(int32 PosX, int32 PosY);
	void AddKeyAndHistory(ACPPSpaceObject* Object, FString Key);

	void CreateUndiscoveredStars(TArray<int32> AllowDirectionList, FVector2d Coords);
	FVector2d CalcNewDelta(int32 Direction);

private:

};
