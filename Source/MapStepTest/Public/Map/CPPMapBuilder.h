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

	//fixme Change FString to Vector2d
	TMap<ACPPSpaceObject*, FString> MaseDict;
	
	TArray<ACPPSpaceObject*> DiscoveryHistory;
	//Methods
public:	
	ACPPMapBuilder();

	virtual void Tick(float DeltaTime) override;
	void AddStartStation(int8 Direction, int8 PosX, int8 PosY, FName Name);

protected:
	virtual void BeginPlay() override;

	FString GenNewKey(int8 PosX, int8 PosY);
	void AddKeyAndHistory(ACPPSpaceObject* Object, FString Key);

	void CreateUndiscoveredStars(TArray<int8> AllowDirectionList, FVector2d Coords);
	FVector2d CalcNewDelta(int8 Direction);

private:

};
