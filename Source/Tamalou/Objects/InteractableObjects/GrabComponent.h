// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/InteractableObject.h"
#include "GrabComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAMALOU_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool isGrabbed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AInteractableObject* OwnerInteractable;

public:
	UGrabComponent();
	
	UFUNCTION()
	bool GetIsGrabbed() const;
	
	UFUNCTION()
	void SetIsGrabbed(bool value);
	
	UFUNCTION()
	virtual void SetOwner(AInteractableObject* _owner);

	UFUNCTION(BlueprintCallable)
	virtual void Grab(APlayerCharacter* _player);
	
	UFUNCTION(BlueprintCallable)
	virtual void UnGrab();
};
