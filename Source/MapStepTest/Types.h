#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types.generated.h"

/*namespace CustomStruct
{*/

USTRUCT(BlueprintType)
struct FStarsStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Star's ID")
	int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Number of Platest")
	int32 NumsPlanet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Star's material")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Star's name")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Star's direction")
	int32 Direction;
};

//}//end namespace CustomStruct



typedef ConstructorHelpers::FObjectFinder<UStaticMesh> CPPStaticMesh;
typedef ConstructorHelpers::FObjectFinder<UMaterial> CPPMaterial;
typedef ConstructorHelpers::FObjectFinder<UMaterialInstance> CPPMaterialInstance;



