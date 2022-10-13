// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPMainGameMode.h"

#include "CPPPlayerController.h"
#include "CPPPlayerPawn.h"


ACPPMainGameMode::ACPPMainGameMode()
{
	DefaultPawnClass = ACPPPlayerPawn::StaticClass();
	PlayerControllerClass = ACPPPlayerController::StaticClass();
}
