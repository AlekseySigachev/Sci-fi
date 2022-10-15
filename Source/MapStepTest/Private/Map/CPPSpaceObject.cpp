// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPSpaceObject.h"

// Sets default values
// ACPPSpaceObject::ACPPSpaceObject()
// {
// 	CentralMesh_= CPPStaticMesh (TEXT("/Game/ProjcetS/StaticMesh/SM_Core"));
// 	Material_ = CPPMaterialInstance (TEXT("/Game/ProjectS/Matrial/MI_Arrow"));
// 	
// }

// ACPPSpaceObject::ACPPSpaceObject()
// {
// 	
// };

// ACPPSpaceObject::ACPPSpaceObject(ConstructorHelpers::FObjectFinder<UStaticMesh> CentralMesh,
// 								CPPMaterialInstance Material ):
// CentralMesh_(CentralMesh),
// Material_(Material)

ACPPSpaceObject::ACPPSpaceObject():
CentralMesh_(new CPPStaticMesh (TEXT("/Game/ProjectS/StaticMesh/SM_Arrow"))),
Material_(new CPPMaterialInstance (TEXT("/Game/ProjectS/Material/MI_Arrow"))),
ArrowMesh_(new CPPStaticMesh (TEXT("/Game/ProjectS/StaticMesh/SM_Arrow"))),
ArrowMaterial_(new CPPMaterialInstance (TEXT("/Game/ProjectS/Material/MI_Arrow")))

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	const FVector Scale = FVector(0.1f, 0.1f, 0.1f);
	FVector Location;
	FRotator Rotator;
	
	// ArrowMesh_ = CPPStaticMesh (TEXT("/Game/ProjectS/StaticMesh/SM_Arrow"));
	// ArrowMaterial_ = CPPMaterialInstance (TEXT("/Game/ProjectS/Material/MI_Arrow"));

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	SceneComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));

	CentralObject = CreateDefaultSubobject<UStaticMeshComponent>("CentralObject");
	CentralObject->SetupAttachment(GetRootComponent());
	CentralObject->SetStaticMesh(CentralMesh_->Object);
	CentralObject->SetMaterial(0, Material_->Object);

	ArrowTop = CreateDefaultSubobject<UStaticMeshComponent>("ArrowTop");
	Rotator = FRotator(0.0f ,180.0f ,0.0f);
	Location = FVector(0.0f, 100.0f, 0.0f);
	AllocateArrow(ArrowTop, ArrowMesh_, ArrowMaterial_, Scale, Location, Rotator);

	ArrowRight = CreateDefaultSubobject<UStaticMeshComponent>("ArrowRight");
	Rotator = FRotator(0.0f ,-90.0f ,0.0f);
	Location = FVector(-100.0f, 0.0f, 0.0f);
	AllocateArrow(ArrowRight, ArrowMesh_, ArrowMaterial_, Scale, Location, Rotator);

	ArrowDown = CreateDefaultSubobject<UStaticMeshComponent>("ArrowDown");
	Rotator = FRotator(0.0f ,0.0f ,0.0f);
	Location = FVector(0.0f, -100.0f, 0.0f);
	AllocateArrow(ArrowDown, ArrowMesh_, ArrowMaterial_, Scale, Location, Rotator);

	ArrowLeft = CreateDefaultSubobject<UStaticMeshComponent>("ArrowLeft");
	Rotator = FRotator(0.0f ,90.0f ,0.0f);
	Location = FVector(100.0f, 0.0f, 0.0f);;
	AllocateArrow(ArrowLeft, ArrowMesh_, ArrowMaterial_, Scale, Location, Rotator);
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

void ACPPSpaceObject::AllocateArrow(UStaticMeshComponent* Arrow, ConstructorHelpers::FObjectFinder<UStaticMesh>* a_ArrowMesh, CPPMaterialInstance* a_ArrowMaterial, FVector Scale, FVector Location, FRotator Rotation)
{
		Arrow->SetupAttachment(GetRootComponent());
		Arrow->SetStaticMesh(a_ArrowMesh->Object);
		Arrow->SetMaterial(0, a_ArrowMaterial->Object);
		Arrow->SetRelativeScale3D(Scale);
		Arrow->SetRelativeLocation(Location);
		Arrow->SetRelativeRotation(Rotation);
}

