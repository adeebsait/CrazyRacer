// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMainMenu.h"
#include "Kismet/GameplayStatics.h"

// Called when Start button is pressed and opens the Level world
void UWidgetMainMenu::StartGame(){
    UGameplayStatics::OpenLevel(GetWorld(), "Level");
}