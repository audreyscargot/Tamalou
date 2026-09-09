// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObject.h"
#include "Door.generated.h"

UCLASS()
class TAMALOU_API ADoor : public AInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool IsLocked;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool DoorIsOpen;

public:
	virtual void Interact_Implementation(APlayerCharacter* _player) override;
	
	UFUNCTION(BlueprintNativeEvent)
	void OpenDoor();
};
