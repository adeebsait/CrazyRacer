// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "ObstacleCharacter.h"
#include "Coin.h"
#include "Tile.generated.h"

UCLASS()
class ENDLESSRACE_API ATile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Model;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* AttachPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChanceToSpawnOnLane=0.75f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AObstacleCharacter> ObstacleClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ACoin> CoinClass;
	UPROPERTY()
		class AEndlessRaceGameModeBase* GMRef;
	UPROPERTY()
		TArray<AObstacleCharacter*> Obstacles;
	UPROPERTY()
		TArray<ACoin*> Coins;
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnObstacles();
	UFUNCTION()
		void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void DelayedDestroy();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
