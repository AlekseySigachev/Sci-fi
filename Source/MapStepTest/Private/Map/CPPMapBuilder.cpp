// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPMapBuilder.h"
#include "Map/CPPSpaceObject_Star.h"
#include "Map/CPPSpaceObject_Station.h"

DEFINE_LOG_CATEGORY_STATIC(MapBuilderLog, All, All);
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

void ACPPMapBuilder::AddKeyAndHistory(ACPPSpaceObject* Object, FVector2d Key)
{
	MaseDict.Add(Object, Key);
	DiscoveryHistory.Add(Object);
	UE_LOG(MapBuilderLog, Display, TEXT("Key: %f:%f added to map"), Key.X, Key.Y);
	UE_LOG(MapBuilderLog, Display, TEXT("Object: %s added to histtory"), *Object->GetName());
}

void ACPPMapBuilder::CreateUndiscoveredStars(TArray<int8> AllowDirectionList, FVector2d Coords)
{
	for (const auto Direction : AllowDirectionList)
	{
		const auto DeltaCoords = CalcNewDelta(Direction);
		FVector2d KeyToFind = FVector2d(DeltaCoords.X, DeltaCoords.Y);
		if(!MaseDict.FindKey(KeyToFind))
		{
			const FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);
			ACPPSpaceObject_Star* Star = GetWorld()->SpawnActorDeferred<ACPPSpaceObject_Star>
													(ACPPSpaceObject_Star::StaticClass(), SpawnTransform);
			if(!Star) return;
			UE_LOG(MapBuilderLog, Display, TEXT("Undiscovered Star: %s created"), *Star->GetName());
			Star->PosX = DeltaCoords.X;
			Star->PosY = DeltaCoords.Y;
			Star->FinishSpawning(SpawnTransform);
			Star->Draw();
			UE_LOG(MapBuilderLog, Display, TEXT("Undiscovered Star: %s initialized"), *Star->GetName());
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
		UE_LOG(MapBuilderLog, Display, TEXT("StartStation: %s initialized"), *StartStation->GetName());
		const FVector2d Key = FVector2d(PosX, PosY);
		AddKeyAndHistory(StartStation, Key);
		CreateUndiscoveredStars(StartStation->GetAllowDirectionList(), StartStation->GetCoords());
	}
}