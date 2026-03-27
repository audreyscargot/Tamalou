// Fill out your copyright notice in the Description page of Project Settings.


#include "Tamalou/Core/GM_Tamalou.h"

#include "TamalouController.h"
#include "Kismet/GameplayStatics.h"

AGM_Tamalou::AGM_Tamalou()
{
	
}

void AGM_Tamalou::BeginPlay()
{
	//Create new character and broadcast arrival
	APlayerController* _temp = UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
}

