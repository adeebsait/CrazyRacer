// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

// Sets default values
ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;	//Setting this actor to call Tick() every frame
	Collision=CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent=Collision;
	Model=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Model->AddRelativeRotation(FRotator(0,5.0f, 0));
}

