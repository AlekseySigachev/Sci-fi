// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CPPPlayerPawn.generated.h"


class ACPPSpaceObject;
class ACPPOrbitalObject;

UCLASS()
class MAPSTEPTEST_API ACPPPlayerPawn : public APawn
{
	GENERATED_BODY()

//Functions
public:
	ACPPPlayerPawn();
	ACPPOrbitalObject* Ship;
	ACPPSpaceObject* CurrentStar;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
private:

//Variables
public:
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		USceneComponent* SceneComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		UCameraComponent* CameraComponent;
private:
};
