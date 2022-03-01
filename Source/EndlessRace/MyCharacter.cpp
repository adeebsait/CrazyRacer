// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "ObstacleCharacter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Coin.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	// Set this character to call Tick() every frame
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}
// Called when coin is collected
void AMyCharacter::IncreasePoints()
{
	Points++;
	if(UI)
	{
		UI->SetPoints(Points);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(Lanes.Num()<3){		// Array to store the fixed positions of the lanes
		Lanes.Empty();
		Lanes.Add(-100.0f);
		Lanes.Add(0.0f);
		Lanes.Add(100.0f);
	}
	if (TimelineCurve) {	// Timeline used for camera switch lane effect
		float Min, Max;
		TimelineCurve->GetTimeRange(Min, Max);
		Timeline.SetTimelineLength(Max);
		Timeline.SetLooping(false);
		Timeline.SetPlayRate(1.0f);
		Timeline.SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
		FOnTimelineFloat UpdateEvent;
		UpdateEvent.BindUFunction(this, "OnTimelineUpdate");
		Timeline.AddInterpFloat(TimelineCurve, UpdateEvent);
		FOnTimelineEvent FinishedEvent;
		FinishedEvent.BindUFunction(this, "OnTimelineFinished");
		Timeline.SetTimelineFinishedFunc(FinishedEvent);
	}
	OnActorBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlap);
	if(UIclass)
	{
		UI = CreateWidget<UWidgetGameUI>(GetWorld(), UIclass);
		UI->AddToViewport();
	}
}
// Called to change lane to right
void AMyCharacter::TurnRight()
{
	if(!bChangingLane && CurrentLane>0)
	{
		bChangingLane=true;
		Pos1=Lanes[CurrentLane--];
		Pos2=Lanes[CurrentLane];
		Timeline.PlayFromStart();
	}
}
// Called to change lane to left
void AMyCharacter::TurnLeft()
{
	if(!bChangingLane && CurrentLane<2)
	{
		bChangingLane=true;
		Pos1=Lanes[CurrentLane++];
		Pos2=Lanes[CurrentLane];
		Timeline.PlayFromStart();
	}
}
// Linear Interpolation of time-based lane switching
void AMyCharacter::OnTimelineUpdate(float Value)
{
	FVector Loc=GetActorLocation();
	float x=FMath::Lerp(Pos1, Pos2, Value);
	Loc.Y=x;
	SetActorLocation(Loc);
}
void AMyCharacter::OnTimelineFinished()
{
	bChangingLane=false;
}
// Check for collision of actors
void AMyCharacter::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	AObstacleCharacter* Obstacle=Cast<AObstacleCharacter>(OtherActor);
	if(Obstacle) //Game over
	{
		Obstacle->Destroy();
		FString s=FString::FromInt(Points);
		FString Dir=FPaths::ProjectDir();
		Dir.Append("save.txt");		//Record of last game score
		FFileHelper::SaveStringToFile(*s,*Dir);
		ShowDeathScreen();
	}
	else{
		ACoin* Coin=Cast<ACoin>(OtherActor);
		if(Coin)	//Collect coin
		{
			IncreasePoints();
			Coin->Destroy();
		}
	}
}
// Stops running of game and shows options
void AMyCharacter::ShowDeathScreen()
{
	if(UI)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		UI->ShowDeathScreen();
	}
}
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
	AddMovementInput(FVector(1,0,0), 1.0f);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("TurnRight", IE_Pressed, this, &AMyCharacter::TurnRight);
	PlayerInputComponent->BindAction("TurnLeft", IE_Pressed, this, &AMyCharacter::TurnLeft);
}