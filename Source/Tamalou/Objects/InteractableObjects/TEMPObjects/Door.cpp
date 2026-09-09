// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Key.h"
#include "Core/PlayerCharacter.h"


// Sets default values
ADoor::ADoor()
{
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Interact_Implementation(APlayerCharacter* _player)
{
	Super::Interact_Implementation(_player);
	if (IsLocked)
	{
		if (_player->GetPhysicHandle()->GetGrabbedComponent() && _player->GetPhysicHandle()->GetGrabbedComponent()->GetOwner()->IsA<ADoorKey>())
		{
			IsLocked = false;
		}
	}
	OpenDoor();
}

void ADoor::OpenDoor_Implementation()
{
	
}

