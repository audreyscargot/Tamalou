// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TamalouController.generated.h"

class UInputMappingContext;

UCLASS()
class TAMALOU_API ATamalouController : public APlayerController
{
	GENERATED_BODY()
	
private:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = true))
	UInputMappingContext* InputMappingContext;
	
	virtual void SetupInputComponent() override;
	
	
};
