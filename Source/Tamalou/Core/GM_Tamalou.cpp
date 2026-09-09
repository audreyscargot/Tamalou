// Fill out your copyright notice in the Description page of Project Settings.


#include "Tamalou/Core/GM_Tamalou.h"
#include "Kismet/GameplayStatics.h"

AGM_Tamalou::AGM_Tamalou()
{
	
}

void AGM_Tamalou::BeginPlay()
{
	//Create new character and broadcast arrival
	if (GetWorld()->GetNumPlayerControllers() < 2)
	{
		APlayerController* _temp = UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
	}
}

