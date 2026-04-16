// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

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

void UGrabComponent::SetOwner(AInteractableObject* _owner)
{
	OwnerInteractable = _owner;
}

void UGrabComponent::Grab(APlayerCharacter* _player)
{
	if (!isGrabbed && OwnerInteractable)
	{
		isGrabbed = true;
		OwnerInteractable->SetActorLocation(_player->GetActorLocation());
		_player->Grab(OwnerInteractable->GetStaticMesh());
	}
}

void UGrabComponent::UnGrab()
{
	if (isGrabbed)
	{
		isGrabbed = false;
	}
}


