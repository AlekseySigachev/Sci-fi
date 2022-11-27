

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CPPHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class MAPSTEPTEST_API UCPPHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* EndTurnButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* GoInside;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* GoOutside;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Move;
};
