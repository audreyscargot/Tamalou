// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/GrabInterface.h"
#include "Tamalou/Interface/InteractInterface.h"
#include "SaveableNPC.generated.h"

class UGrabComponent;
class USphereComponent;

UCLASS()
class TAMALOU_API ASaveableNPC : public ACharacter, public IGrabInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	UGrabComponent* GrabComponent;

public:
	// Sets default values for this character's properties
	ASaveableNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	FName GrabbedBoneName;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Grab_Implementation(APlayerCharacter* _player) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void GetClosestBone(FVector _playerLocation);
};
