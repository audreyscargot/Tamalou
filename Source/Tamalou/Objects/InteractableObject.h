// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tamalou/Interface/InteractInterface.h"
#include "InteractableObject.generated.h"

class USphereComponent;

UCLASS()
class TAMALOU_API AInteractableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;


public:
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APlayerCharacter* _player) override;
};
