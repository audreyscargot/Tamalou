// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Camera/CameraActor.h"
#include "GM_Tamalou.generated.h"

class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerCreated);

UCLASS()
class TAMALOU_API AGM_Tamalou : public AGameModeBase
{
	GENERATED_BODY()
	
	AGM_Tamalou();
	
public:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	FOnPlayerCreated OnPlayerCreated;
};
