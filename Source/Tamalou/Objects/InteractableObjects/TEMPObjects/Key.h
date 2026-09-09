// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjects/GrabObjectBase.h"
#include "Key.generated.h"

UCLASS()
class TAMALOU_API ADoorKey : public AGrabObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Grab_Implementation(APlayerCharacter* _player) override;
};
