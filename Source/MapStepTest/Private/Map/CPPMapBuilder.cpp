// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPMapBuilder.h"
#include "Map/CPPSpaceObject_Star.h"
#include "Map/CPPSpaceObject_Station.h"

// Sets default values
ACPPMapBuilder::ACPPMapBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACPPMapBuilder::BeginPlay()
{
	Super::BeginPlay();
	AddStartStation(15, 0, 0, "StartStation");
}

FString ACPPMapBuilder::GenNewKey(int8 PosX, int8 PosY)
{
	FString Key = FString::Printf(TEXT("%d_%d"), PosX, PosY);
	return Key;
}

void ACPPMapBuilder::AddKeyAndHistory(ACPPSpaceObject* Object, FString Key)
{
	MaseDict.Add(Object, Key);
	DiscoveryHistory.Add(Object);
}

void ACPPMapBuilder::CreateUndiscoveredStars(TArray<int8> AllowDirectionList, FVector2d Coords)
{
	for (const auto Direction : AllowDirectionList)
	{
		const auto DeltaCoords = CalcNewDelta(Direction);
		FString KeyToFind = GenNewKey(DeltaCoords.X, DeltaCoords.Y);
		if(!MaseDict.FindKey(KeyToFind))
		{
			const FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
			ACPPSpaceObject_Star* Star = GetWorld()->SpawnActorDeferred<ACPPSpaceObject_Star>
													(ACPPSpaceObject_Star::StaticClass(), SpawnTransform);
			Star->PosX = DeltaCoords.X;
			Star->PosY = DeltaCoords.Y;
			Star->FinishSpawning(SpawnTransform);
			Star->Draw();
			MaseDict.Add(Star, KeyToFind);
		}
	}
}

FVector2d ACPPMapBuilder::CalcNewDelta(int8 Direction)
{
	switch (Direction)
	{
	case 1: return FVector2d(0.0f, 1.0f);
	case 2: return FVector2d(-1.0f, 0.0f);
	case 4: return FVector2d(0.0f, -1.0f);
	case 8: return FVector2d(1.0f, 0.0f);
	
	default: return FVector2d::ZeroVector;
	
	}
}

// Called every frame
void ACPPMapBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPPMapBuilder::AddStartStation(int8 Direction, int8 PosX, int8 PosY, FName Name)
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
	ACPPSpaceObject_Station* StartStation = GetWorld()->SpawnActorDeferred<ACPPSpaceObject_Station>
											(ACPPSpaceObject_Station::StaticClass(), SpawnTransform);
	
	if (StartStation)
	{
		StartStation->PosX = PosX;
		StartStation->PosY = PosY;
		StartStation->Direction = Direction;
		StartStation->Name = Name;
		StartStation->FinishSpawning(SpawnTransform);
		StartStation->OnDiscovered();
		StartStation->Draw();
		const FString Key = GenNewKey(PosX,PosY);
		AddKeyAndHistory(StartStation, Key);
		CreateUndiscoveredStars(StartStation->GetAllowDirectionList(), StartStation->GetCoords());
	}
}