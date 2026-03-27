// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "PlayerCharacter.generated.h"

class AInteractableObject;
class USphereComponent;
class UPhysicalAnimationComponent;

UCLASS()
class TAMALOU_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	UPhysicalAnimationComponent* PhysicalAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ragdoll", meta = (AllowPrivateAccess = true))
	FName boneName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ragdoll", meta = (AllowPrivateAccess = true))
	FPhysicalAnimationData physAnimData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AActor* interactableObject;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	virtual void Move(const FInputActionValue& _value);
	
	UFUNCTION()
	virtual void DoMove(float _right, float _forward);
	
	UFUNCTION()
	virtual void CheckForInteract();
	
	UFUNCTION()
	virtual void Interact();
};
