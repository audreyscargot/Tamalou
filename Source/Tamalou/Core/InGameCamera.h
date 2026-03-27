// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameCamera.generated.h"

class AGM_Tamalou;
class USpringArmComponent;
class APlayerCharacter;
class UCameraComponent;

UCLASS()
class TAMALOU_API AInGameCamera : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;
	
public:	
	// Sets default values for this actor's properties
	AInGameCamera();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaTime ) override;
	
	UPROPERTY()
	AGM_Tamalou* gameMode;
	
	UPROPERTY()
	FVector playersLocationSum;
	
	UPROPERTY()
	int playersNumber;
	
	
	//Target arm length ZOOM variables
	UPROPERTY()
	float currentDistFromCenterPoint;
	
	UPROPERTY()
	float minArmLengthValue;
	
	//TODO : modify values depending n desired results
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float minDistFromCenter = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float maxDistFromCenter = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float minZoom = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float maxZoom = 1.5f;

public:	
	
	UFUNCTION()
	virtual void MakePlayersNum();

	UFUNCTION()
	virtual void UpdateCamera();
	
	UFUNCTION()
	virtual void UpdateCameraZoom();
};
