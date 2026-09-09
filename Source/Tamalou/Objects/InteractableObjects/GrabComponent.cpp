// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

#include "GrabObjectBase.h"
#include "Core/PlayerCharacter.h"


// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	
}

bool UGrabComponent::GetIsGrabbed() const
{
	return isGrabbed;
}

void UGrabComponent::SetIsGrabbed(bool value)
{
	isGrabbed = value;
}

void UGrabComponent::SetOwner(AGrabObjectBase* _owner)
{
	OwnerInteractable = _owner;
}

void UGrabComponent::Grab(APlayerCharacter* _player)
{
	if (!isGrabbed && OwnerInteractable)
	{
		isGrabbed = true;
		OwnerInteractable->SetActorLocation(_player->GetActorLocation());
	}
}

void UGrabComponent::UnGrab()
{
	if (isGrabbed)
	{
		if (OwnerInteractable) OwnerInteractable->IsUnGrabbed();
		isGrabbed = false;
	}
}


