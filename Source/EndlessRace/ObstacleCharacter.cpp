// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleCharacter.h"

// Sets default values
AObstacleCharacter::AObstacleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;		// Set this character to call Tick() every frame.

}

// Called when the game starts or when spawned
void AObstacleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(FVector(1,0, 0), -1.0f, true);		// Add velocity of obstacles
}