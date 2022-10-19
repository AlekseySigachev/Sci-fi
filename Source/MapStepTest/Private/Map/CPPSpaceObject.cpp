// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPSpaceObject.h"

#include "Engine/DataTable.h"

ACPPSpaceObject::ACPPSpaceObject()

{
	PrimaryActorTick.bCanEverTick = true;
	
	const FVector Scale = FVector(0.1f, 0.1f, 0.1f);
	FVector Location;
	FRotator Rotation;

	//Default mesh and material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoreMesh(TEXT("/Game/ProjectS/StaticMesh/SM_Core"));
	UStaticMesh* SM_Core = CoreMesh.Object;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMesh(TEXT("/Game/ProjectS/StaticMesh/SM_Arrow"));
	UStaticMesh* SM_Arrow = ArrowMesh.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> ArrowMaterial(TEXT("/Game/ProjectS/Material/MI_Arrow"));
	UMaterialInstance* MI_Arrow = ArrowMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultOpenMaterial(TEXT("/Game/ProjectS/Material/Red"));
	OpenMaterial = DefaultOpenMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultCloseMaterial(TEXT("/Game/ProjectS/Material/Blue"));
	CloseMaterial = DefaultCloseMaterial.Object;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	SceneComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));

	CentralObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CentralObject"));
	CentralObject->SetupAttachment(GetRootComponent());
	CentralObject->SetStaticMesh(SM_Core);
	CentralObject->SetMaterial(0, MI_Arrow);

	ArrowTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowTop"));
	Rotation = FRotator(0.0f ,180.0f ,0.0f);
	Location = FVector(0.0f, 100.0f, 0.0f);
	AllocateArrow(ArrowTop, SM_Arrow, MI_Arrow, Scale, Location, Rotation);

	ArrowRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowRight"));
	Rotation = FRotator(0.0f ,-90.0f ,0.0f);
	Location = FVector(-100.0f, 0.0f, 0.0f);
	AllocateArrow(ArrowRight, SM_Arrow, MI_Arrow, Scale, Location, Rotation);

	ArrowDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowDown"));
	Rotation = FRotator(0.0f ,0.0f ,0.0f);
	Location = FVector(0.0f, -100.0f, 0.0f);
	AllocateArrow(ArrowDown, SM_Arrow, MI_Arrow, Scale, Location, Rotation);
	
	ArrowLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowLeft"));
	Rotation = FRotator(0.0f ,90.0f ,0.0f);
	Location = FVector(100.0f, 0.0f, 0.0f);;
	AllocateArrow(ArrowLeft, SM_Arrow, MI_Arrow, Scale, Location, Rotation);
}

void ACPPSpaceObject::BeginPlay()
{
	Super::BeginPlay();
	CentralObject->OnClicked.AddDynamic(this, &ACPPSpaceObject::OnClicked);
}

void ACPPSpaceObject::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Error, TEXT("Test with %s"),*TouchedComponent->GetName());
}

void ACPPSpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPPSpaceObject::OnDiscovered()
{
	DrawArrows();
	CentralObject->SetMaterial(0, OpenMaterial);
}

void ACPPSpaceObject::SetProperties(FString name, int32 direction, int32 planetquantity, UMaterialInterface* material)
{
	Name = name;
	Direction = direction;
	OpenMaterial = material;
}


void ACPPSpaceObject::AllocateArrow(UStaticMeshComponent* Arrow,
                                    UStaticMesh* Mesh,
                                    UMaterialInstance* Material,
                                    FVector Scale,
                                    FVector Location,
                                    FRotator Rotation) const
{
		Arrow->SetupAttachment(GetRootComponent());
		Arrow->SetStaticMesh(Mesh);
		Arrow->SetMaterial(0, Material);
		Arrow->SetRelativeScale3D(Scale);
		Arrow->SetRelativeLocation(Location);
		Arrow->SetRelativeRotation(Rotation);
		Arrow->SetVisibility(false);
}

FVector2d ACPPSpaceObject::GetCoords() const
{
	return FVector2d(PosX, PosY);
}

int32 ACPPSpaceObject::GetGridStep() const
{
	return GridStep;
}

void ACPPSpaceObject::EnableArrowTop()
{
	ArrowTop->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowRight()
{
	ArrowRight->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowDown()
{
	ArrowDown->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowLeft()
{
	ArrowLeft->SetVisibility(true);
}

void ACPPSpaceObject::DisableArrowTop()
{
	ArrowTop->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowRight()
{
	ArrowRight->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowDown()
{
	ArrowDown->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowLeft()
{
	ArrowLeft->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowAndDirection(int32 direction)
{
	switch (direction)
	{
	case 1:
		{
			DisableArrowTop();
			DisableDirection(direction);
			break;
		}
	case 2:
		{
			DisableArrowRight();
			DisableDirection(direction);
			break;
		}
	case 4:
		{
			DisableArrowDown();
			DisableDirection(direction);
			break;
		}
	case 8:
		{
			DisableArrowLeft();
			DisableDirection(direction);
			break;
		}
	}
}

void ACPPSpaceObject::EnableArrowAndDirection(int32 direction)
{
	switch (direction)
	{
	case 1:
		{
			EnableArrowTop();
			EnableDirection(direction);
			break;
		}
	case 2:
		{
			EnableArrowRight();
			EnableDirection(direction);
			break;
		}
	case 4:
		{
			EnableArrowDown();
			EnableDirection(direction);
			break;
		}
	case 8:
		{
			EnableArrowLeft();
			EnableDirection(direction);
			break;
		}
	}
}

bool ACPPSpaceObject::CanMoveTop()
{
	return CalcDirection(1)== 1;
}

bool ACPPSpaceObject::CanMoveDown()
{
	return CalcDirection(4)== 4;
}

bool ACPPSpaceObject::CanMoveRight()
{
	return CalcDirection(2)== 2;
}

bool ACPPSpaceObject::CanMoveLeft()
{
	return CalcDirection(8)== 8;
}

int32 ACPPSpaceObject::CalcDirection(int32 CalcDirection)
{
	return  CalcDirection & Direction;
}

void ACPPSpaceObject::EnableDirection(int32 direction)
{
	Direction = direction | Direction;
}
void ACPPSpaceObject::DisableDirection(int32 direction)
{
	Direction = ~direction & Direction;
}

TArray<int32> ACPPSpaceObject::GetAllowDirectionList()
{
	TArray<int32> DirectionList;
	CanMoveTop() ? DirectionList.Add(1) : NULL;
	CanMoveRight() ? DirectionList.Add(2) : NULL;
	CanMoveDown() ? DirectionList.Add(4) : NULL;
	CanMoveLeft() ? DirectionList.Add(8) : NULL;
	return DirectionList;
}

void ACPPSpaceObject::DrawArrows()
{
	CanMoveTop() ? EnableArrowTop() : NULL;
	CanMoveRight() ? EnableArrowRight() : NULL;
	CanMoveDown() ? EnableArrowDown() : NULL;
	CanMoveLeft() ? EnableArrowLeft() : NULL;
}

void ACPPSpaceObject::Draw()
{
	auto LocationX = (PosX*GridStep);
	auto LocationY = (PosY*GridStep);
	const FVector NewLocation = FVector(LocationX, LocationY, 0.0f);
	SetActorLocation(NewLocation);
}
