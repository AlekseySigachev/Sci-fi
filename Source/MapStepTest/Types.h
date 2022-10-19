#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types.generated.h"

USTRUCT(BlueprintType)
struct FStarsStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NumsPlanet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanBeDiscovered;
};


typedef ConstructorHelpers::FObjectFinder<UStaticMesh> CPPStaticMesh;
typedef ConstructorHelpers::FObjectFinder<UMaterial> CPPMaterial;
typedef ConstructorHelpers::FObjectFinder<UMaterialInstance> CPPMaterialInstance;



