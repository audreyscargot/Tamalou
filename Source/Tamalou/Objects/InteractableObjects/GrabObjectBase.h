// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GrabInterface.h"
#include "GrabObjectBase.generated.h"

class UGrabComponent;
class USphereComponent;

UCLASS()
class TAMALOU_API AGrabObjectBase : public AActor, public IGrabInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UGrabComponent* GrabComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UStaticMeshComponent* StaticMesh;

public:
	// Sets default values for this actor's properties
	AGrabObjectBase();
	
	virtual void BeginPlay() override;
	
	UStaticMeshComponent* GetStaticMesh();
	
	virtual void Grab_Implementation(APlayerCharacter* _player) override;
	
	UFUNCTION()
	void IsUnGrabbed();
	
};
