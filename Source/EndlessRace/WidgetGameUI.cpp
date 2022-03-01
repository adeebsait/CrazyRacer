// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetGameUI.h"
#include "Kismet/GameplayStatics.h"

// Always show current score
void UWidgetGameUI::SetPoints(int32 Value)
{
    if(Points)
    {
        Points->SetText(FText::AsNumber(Value));
    }
}
// Restart and Main Menu buttons are shown when called
void UWidgetGameUI::ShowDeathScreen()
{
    if(DeathBox)
    {
        DeathBox->SetVisibility(ESlateVisibility::Visible);
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if(PC)
        {
            PC->bShowMouseCursor=true;
        }
    }
}
// Called when restart key is pressed to open the Level world with gameplay
void UWidgetGameUI::RestartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Level");
}
// Called when Main Menu key is pressed to open the Main Menu world which contains only UI
void UWidgetGameUI::OpenMainMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}