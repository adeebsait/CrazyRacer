// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "EndlessRaceGameModeBase.h"
// Sets the number of tiles spawned each time
void AEndlessRaceGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    for(int i=0;i<5;i++)
    {
        SpawnTile();
    }
}
// Spawns the road and attached next spawn point to end of tile
void AEndlessRaceGameModeBase::SpawnTile()
{
    ATile* Tile=(ATile*)GetWorld()->SpawnActor(TileClass, &NextSpawnPoint);
    if(Tile)
    {
        Tile->GMRef=this;
        NextSpawnPoint=Tile->AttachPoint->GetComponentLocation();
    }
}