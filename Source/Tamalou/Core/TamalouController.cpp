// Fill out your copyright notice in the Description page of Project Settings.


#include "Tamalou/Core/TamalouController.h"

#include "CameraManager.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

void ATamalouController::BeginPlay()
{
	Super::BeginPlay();
}

void ATamalouController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}
