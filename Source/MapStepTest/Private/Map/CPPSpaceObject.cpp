// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPSpaceObject.h"

// Sets default values
ACPPSpaceObject::ACPPSpaceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CentralObject = CreateDefaultSubobject<UStaticMeshComponent>("CentralObject");
	CentralObject->SetupAttachment(GetRootComponent());

	ArrowTop = CreateDefaultSubobject<UStaticMeshComponent>("ArrowTop");
	ArrowTop->SetupAttachment(GetRootComponent());

	ArrowRight = CreateDefaultSubobject<UStaticMeshComponent>("ArrowRight");
	ArrowRight->SetupAttachment(GetRootComponent());

	ArrowDown = CreateDefaultSubobject<UStaticMeshComponent>("ArrowDown");
	ArrowDown->SetupAttachment(GetRootComponent());

	ArrowLeft = CreateDefaultSubobject<UStaticMeshComponent>("ArrowLeft");
	ArrowLeft->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void ACPPSpaceObject::BeginPlay()
{
	Super::BeginPlay();
	CentralObject->OnClicked.AddDynamic(this, &ACPPSpaceObject::OnClicked);
}

void ACPPSpaceObject::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Error, TEXT("Test with %s"),*TouchedComponent->GetName());
}

// Called every frame
void ACPPSpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

