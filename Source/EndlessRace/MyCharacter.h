// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "WidgetGameUI.h"
#include "MyCharacter.generated.h"

UCLASS()
class ENDLESSRACE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Points;
	// Sets default values for this character's properties
	AMyCharacter();
	void IncreasePoints();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWidgetGameUI> UIclass;
	UPROPERTY()
		UWidgetGameUI* UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* TimelineCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> Lanes;
	bool bChangingLane=false;
	int32 CurrentLane=1; // Starting in middle lane
	float Pos1, Pos2;
	FTimeline Timeline;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void TurnRight();
	UFUNCTION()
		void TurnLeft();
	UFUNCTION()
		void OnTimelineUpdate(float Value);
	UFUNCTION()
		void OnTimelineFinished();
	UFUNCTION()
		void OnOverlap(AActor* MyActor, AActor* OtherActor);
	void ShowDeathScreen();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
