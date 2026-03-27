// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Tamalou/Interface/InteractInterface.h"
#include "Engine/EngineTypes.h"
#include "SaveableNPC.generated.h"

class USphereComponent;

UCLASS()
class TAMALOU_API ASaveableNPC : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

public:
	// Sets default values for this character's properties
	ASaveableNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool isGrabbed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Interact_Implementation(APlayerCharacter* _player) override;
};
