// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
#include "MapStepTest/Types.h"
#include "MapStepTest/Const.h"
#include "CPPSpaceObject.generated.h"


UCLASS()
class MAPSTEPTEST_API ACPPSpaceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaTime) override;

	ACPPSpaceObject();
	// ACPPSpaceObject(CPPStaticMesh CentralMesh, CPPMaterialInstance Material);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* CentralObject;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowTop;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowRight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowDown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* ArrowLeft;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

protected:
	void AllocateArrow(UStaticMeshComponent *Arrow,
								ConstructorHelpers::FObjectFinder<UStaticMesh>* a_ArrowMesh,
								ConstructorHelpers::FObjectFinder<UMaterialInstance>* a_ArrowMaterial,
								FVector Scale,
								FVector Location,
								FRotator Rotation );
	
private:

//variables
public:
protected:
	CPPStaticMesh* CentralMesh_;
	CPPMaterialInstance* Material_;
	CPPStaticMesh* ArrowMesh_;
	CPPMaterialInstance* ArrowMaterial_;
	
private:

};
