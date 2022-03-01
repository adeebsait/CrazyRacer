// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "MyCharacter.h"
#include "EndlessRaceGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATile::ATile()
{
 	
	PrimaryActorTick.bCanEverTick = true;		// Set this actor to call Tick() every frame
	RootScene=CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent=RootScene;
	Model=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(RootComponent);
	AttachPoint=CreateDefaultSubobject<UArrowComponent>(TEXT("Attach"));
	AttachPoint->SetupAttachment(RootComponent);
	Trigger=CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnCollisionBegin);
	SpawnObstacles();
}
// Spawns coin and car actors on the road randomly
void ATile::SpawnObstacles()
{
	int32 Cars=0;
	FVector Location=GetActorLocation();
	Location.X+=1000.0f;
	Location.Y-=350.0f;
	FTransform Transform;
	for(int i=0;i<3;i++){
		if(UKismetMathLibrary::RandomBoolWithWeight(ChanceToSpawnOnLane)) // Spawn car or coin on lane i
		{
			if(UKismetMathLibrary::RandomBool())// Spawn car
			{
				if(Cars<2)
				{
					Location.Z=100.0f;
					Transform.SetLocation(Location);
					AObstacleCharacter* Obstacle=(AObstacleCharacter*)GetWorld()->SpawnActor(ObstacleClass, &Transform);
					if(Obstacle)
					{
						Obstacles.Add(Obstacle);
						Cars++;
					}
				}
			}
			else // Spawn coin
			{
				Location.Z=50.0f;
				Transform.SetLocation(Location);
				ACoin* Coin=(ACoin*)GetWorld()->SpawnActor(CoinClass, &Transform);
				if(Coin)
				{
					Coins.Add(Coin);
				}
			}
		}
		Location.Y+=350.0f;
	}
}
// Called when player car collides with trigger to spawn next set of tiles(road)
void ATile::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Player=Cast<AMyCharacter>(OtherActor);
	if(Player && GMRef)
	{
		GMRef->SpawnTile();
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATile::DelayedDestroy, 2.0f, false);
	}
}
// Destroying objects that the user has passed through
void ATile::DelayedDestroy()
{
	for(auto Obstacle: Obstacles)
	{
		if(Obstacle)
		{
			Obstacle->Destroy();
		}
	}
	for(auto Coin: Coins)
	{
		if(Coin)
		{
			Coin->Destroy();
		}
	}
	Destroy();
}
// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

