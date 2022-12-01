// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Map/CPPScene.h>
#include "GameFramework/GameModeBase.h"
#include "CPPMainGameMode.generated.h"


class ACPPSpaceObject;
class ACPPSpaceObject_Station;
class ACPPPlayerPawn;
class ACPPPlayerController;
class UCPPHUDWidget;
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
	void OnOffMoveButton(bool Switch);
	void MoveShipToLocation();
	void PossessFirstPlayer();
	void PossessNextPlayer();

protected:
	virtual void BeginPlay() override;
private:

	void CreateHUDWidget();
	void ReallocatePlayer();
	void ToggleInsideButton(ACPPSpaceObject* Target);
	void DrawScene();

//Variables

public:
	TArray<ACPPPlayerPawn*> Players;
	ACPPSpaceObject_Station* StartStation;
	ACPPPlayerController* PlayerController;
	ACPPPlayerPawn* CurrentPlayer;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	//TODO
	ACPPScene* MainScene;
	ACPPScene* SubScene;
	//SolarSystemBuilder
protected:
private:
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<AActor> PlayerClass;
	UCPPHUDWidget* HUD;
	FVector Delta = FVector(600.0f, 0.0f, 0.0f);
};
