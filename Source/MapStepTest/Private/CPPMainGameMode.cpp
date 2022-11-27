// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPMainGameMode.h"

#include "CPPPlayerController.h"
#include "CPPMainGameInstance.h"
#include "CPPPlayerPawn.h"
#include "CPPPlayerShip.h"
#include "Map/CPPOrbitalObject.h"
#include "Map/CPPSpaceObject_Station.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


ACPPMainGameMode::ACPPMainGameMode()
{
	DefaultPawnClass = ACPPPlayerPawn::StaticClass();
	PlayerControllerClass = ACPPPlayerController::StaticClass();
}
void ACPPMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	StartStation = Cast<ACPPSpaceObject_Station>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPPSpaceObject_Station::StaticClass()));
	SpawnPlayers(StartStation);
	CreateHUDWidget();
	ReallocatePlayer();
}

void ACPPMainGameMode::PossessFirstPlayer()
{
	CurrentPlayer = Players[0];
	PlayerController->Possess(CurrentPlayer);
}
void ACPPMainGameMode::PossessNextPlayer()
{
	auto NextPlayerIndex = Players.Find(CurrentPlayer) + 1;
	if (Players.Num() < NextPlayerIndex)
	{
		CurrentPlayer = Players[NextPlayerIndex];
		PlayerController->Possess(CurrentPlayer);
	}
	else
	{
		PossessFirstPlayer();
	}
}
void ACPPMainGameMode::CreateHUDWidget()
{
	HUD = CreateWidget<UCPPHUDWidget>(GetWorld(), HUDWidgetClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void ACPPMainGameMode::ReallocatePlayer()
{
	for (int i = 0; i < Players.Num(); i++)
	{
		if (StartStation->Positions.IsEmpty()) return;
		Players[i]->SetActorLocation(StartStation->Positions[i]);
	}
}

void ACPPMainGameMode::ToggleInsideButton(ACPPSpaceObject* Target)
{
	HUD->GoInside->SetIsEnabled(Target->CanGoInside() && Target->bDiscovered);
}

int8 ACPPMainGameMode::GetPlayerQuantity()
{
	const auto GameInstance = Cast<UCPPMainGameInstance>(GetGameInstance());
	return GameInstance->PlayersQuantity;
}

void ACPPMainGameMode::SpawnPlayers(ACPPSpaceObject_Station* Station)
{
	for (int i = 0; i <= GetPlayerQuantity(); i++)
	{
		FActorSpawnParameters SpawnInfo;
		
		if (!PlayerClass) return;
		auto Player = GetWorld()->SpawnActor<ACPPPlayerPawn>(PlayerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		Players.Add(Player);
		Station->AddSpaceObjectToOrbit(Player->Ship);
		Player->CurrentStar = Station;
		auto PlayersShip = Cast<ACPPPlayerShip>(Player->Ship);
		PlayersShip->CurrentStar = Station;
		if (i == GetPlayerQuantity())
		{
			PossessFirstPlayer();
			Station->CalcObjectsPositionsOnOrbit();
			Station->ReallocateObjectsOnOrbit();
		} 
	}
}

void ACPPMainGameMode::MovePlayerToLocations(ACPPSpaceObject* Target)
{
	ToggleInsideButton(Target);
	CurrentPlayer->CurrentStar = Target;
	auto StarLocation = CurrentPlayer->CurrentStar->GetActorLocation();
	CurrentPlayer->SetActorLocation(FVector(StarLocation.X, StarLocation.Y, 0.0f));
	auto PlayerShip = Cast<ACPPPlayerShip>(CurrentPlayer->Ship);
	CheckAllowedDirection(CurrentPlayer->CurrentStar, PlayerShip->CurrentStar);
}

void ACPPMainGameMode::CheckAllowedDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar)
{
	auto DirectionList = ShipStar->GetAllowDirectionList();
	auto ReqDirection = GetRequieredDirection(PlayerStar, ShipStar);
}

int8 ACPPMainGameMode::GetRequieredDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar)
{
	int8 LDirection = 0;
	auto PlayerStarLocation = PlayerStar->GetActorLocation();
	auto ShipStarLocation = ShipStar->GetActorLocation();
	if ((ShipStarLocation != PlayerStarLocation))
	{
		auto GridStep = PlayerStar->GetGridStep();
		auto LocationsSubtruct = ShipStarLocation - PlayerStarLocation;
		auto bHereOnPosX = (FMath::Abs(LocationsSubtruct.X / GridStep) == 1);
		auto bHereOnPosY = (FMath::Abs(LocationsSubtruct.Y / GridStep) == 1);
		auto bNotHereOnPosX = (FMath::Abs(LocationsSubtruct.X / GridStep) == 0);
		auto bNotHereOnPosY = (FMath::Abs(LocationsSubtruct.Y / GridStep) == 0);
		if (!(bHereOnPosX || bHereOnPosY))
		{
			return LDirection;
		}
		else if(!(bNotHereOnPosX && bNotHereOnPosY))
		{
			return LDirection;
		}
		else if (bNotHereOnPosX)
		{
			return TopDownMove(ShipStarLocation, PlayerStarLocation);
		}
		else
		{
			return LeftRightMove(ShipStarLocation, PlayerStarLocation);
		}
		if (bNotHereOnPosY)
		{
			return LeftRightMove(ShipStarLocation, PlayerStarLocation);
		}
		else
		{
			return TopDownMove(ShipStarLocation, PlayerStarLocation);
		}
	}
	else
	{
		return LDirection;
	}
}

int8 ACPPMainGameMode::TopDownMove(FVector ShipLoc, FVector PlayerLoc)
{
	if ((ShipLoc.Y - PlayerLoc.Y) < 0) 
	{
		return 1;
	}
	else
	{
		return 4;
	}

}

int8 ACPPMainGameMode::LeftRightMove(FVector ShipLoc, FVector PlayerLoc)
{
	if ((ShipLoc.X - PlayerLoc.X) > 0)
	{
		return 2;
	}
	else
	{
		return 8;
	}
}
