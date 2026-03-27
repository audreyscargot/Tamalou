// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraManager.generated.h"

class AInGameCamera;

UCLASS()
class TAMALOU_API ACameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AInGameCamera> CameraClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AInGameCamera* Camera;
	
public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void SetCamera();
};
