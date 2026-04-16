// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableObject.generated.h"

class UDestroyableComponent;
class UBoxComponent;

UCLASS()
class TAMALOU_API ABreakableObject : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Components")
	UDestroyableComponent* DestroyableComponent;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Properties")
	bool isBroken;

public:
	// Sets default values for this actor's properties
	ABreakableObject();
	
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	 * redéfinir la condition pour chaque enfant : si condition checked alors se destroy (condition checked = true de base)
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ConditionChecked();
};
