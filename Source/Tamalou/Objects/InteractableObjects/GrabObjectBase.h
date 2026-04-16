// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/InteractableObject.h"
#include "GrabObjectBase.generated.h"

class UGrabComponent;
class USphereComponent;

UCLASS()
class TAMALOU_API AGrabObjectBase : public AInteractableObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UGrabComponent* GrabComponent;

public:
	// Sets default values for this actor's properties
	AGrabObjectBase();
	
	virtual void Interact_Implementation(APlayerCharacter* _player) override;
	
};
