// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "WidgetGameUI.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRACE_API UWidgetGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* Points;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UVerticalBox* DeathBox;
	void SetPoints(int32 Value);
	void ShowDeathScreen();
	UFUNCTION(BlueprintCallable)
		void RestartGame();
	UFUNCTION(BlueprintCallable)
		void OpenMainMenu();
};
