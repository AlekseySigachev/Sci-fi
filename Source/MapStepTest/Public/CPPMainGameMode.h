// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UserInterface/CPPHUDWidget.h"
#include "CPPMainGameMode.generated.h"

class ACPPSpaceObject;
class ACPPSpaceObject_Station;
class ACPPPlayerPawn;
class ACPPPlayerController;
/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API ACPPMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ACPPMainGameMode();

//Functions

public:
	int8 GetPlayerQuantity();
	void SpawnPlayers(ACPPSpaceObject_Station* Station);
	void MovePlayerToLocations(ACPPSpaceObject* Target);
	void CheckAllowedDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar);
	int8 GetRequieredDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar);
	int8 TopDownMove(FVector ShipLoc, FVector PlayerLoc);
	int8 LeftRightMove(FVector ShipLoc, FVector PlayerLoc);

protected:
	virtual void BeginPlay() override;
private:
	void PossessFirstPlayer();
	void PossessNextPlayer();
	void CreateHUDWidget();
	void ReallocatePlayer();
	void ToggleInsideButton(ACPPSpaceObject* Target);

//Variables

public:
	TArray<ACPPPlayerPawn*> Players;
	ACPPSpaceObject_Station* StartStation;
	ACPPPlayerController* PlayerController;
	ACPPPlayerPawn* CurrentPlayer;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	//TODO
	//MainScene
	//SolarSystemBuilder
protected:
private:
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<AActor> PlayerClass;
	UCPPHUDWidget* HUD;
};
