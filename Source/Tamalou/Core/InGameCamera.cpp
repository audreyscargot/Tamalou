// Fill out your copyright notice in the Description page of Project Settings.


#include "Tamalou/Core/InGameCamera.h"
#include "Kismet/GameplayStatics.h"
#include "GM_Tamalou.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInGameCamera::AInGameCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SetRootComponent(CameraBoom);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInGameCamera::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AGM_Tamalou>(UGameplayStatics::GetGameMode(this));
	MakePlayersNum();
	minArmLengthValue = CameraBoom->TargetArmLength;
}

void AInGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCamera();
}

void AInGameCamera::MakePlayersNum()
{
	if (gameMode)
	{
		playersNumber = gameMode->GetNumPlayers();
		playersLocationSum = FVector(0,0,0);
	}
	SetActorTickEnabled(true);
}

void AInGameCamera::UpdateCamera()
{
	playersLocationSum = FVector(0,0,0);
	for (int i = 0; i < playersNumber; i++)
	{
		playersLocationSum += UGameplayStatics::GetPlayerPawn(this, i)->GetActorLocation();
	}
	SetActorLocation(playersLocationSum/playersNumber);
	UpdateCameraZoom();
}

void AInGameCamera::UpdateCameraZoom()
{
	currentDistFromCenterPoint = 0;
	for (int i = 0; i < playersNumber-1; i++)
	{
		FVector _tempLoc = UGameplayStatics::GetPlayerPawn(this,i)->GetActorLocation();
		float _dist = UKismetMathLibrary::Vector_Distance(_tempLoc, GetActorLocation());
		if (_dist > currentDistFromCenterPoint)
		{
			currentDistFromCenterPoint = _dist;
		}
		CameraBoom->TargetArmLength = UKismetMathLibrary::MapRangeClamped(currentDistFromCenterPoint, minDistFromCenter, maxDistFromCenter, minZoom ,maxZoom) * minArmLengthValue; 
	}
}





