// Fill out your copyright notice in the Description page of Project Settings.


#include "Tamalou/Core/CameraManager.h"
#include "Tamalou/Core/InGameCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BEGINPLAY"));
	SetCamera();
}

void ACameraManager::SetCamera()
{
	if (GetOwningPlayerController() && GetOwningPlayerController()->GetLocalPlayerConnectionIdentifier() == 0 && CameraClass)
	{
		//Spawn camera
		FVector _location = FVector(0,0,0);
		FRotator _rotation = FRotator(0,0,0);
		FActorSpawnParameters SpawnInfo;
		Camera = GetWorld()->SpawnActor<AInGameCamera>(CameraClass, _location, _rotation, SpawnInfo);
	
		GetOwningPlayerController()->SetViewTarget(Camera);
	}
	UE_LOG(LogTemp, Warning, TEXT("DONE"));
}
