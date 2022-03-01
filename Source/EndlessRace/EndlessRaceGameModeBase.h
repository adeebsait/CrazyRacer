// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tile.h"
#include "EndlessRaceGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRACE_API AEndlessRaceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void SpawnTile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATile> TileClass;
	FVector NextSpawnPoint;
	virtual void BeginPlay() override;
};
