// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabObjectBase.h"

#include "GrabComponent.h"
#include "Core/PlayerCharacter.h"


// Sets default values
AGrabObjectBase::AGrabObjectBase()
{
	GrabComponent = CreateDefaultSubobject<UGrabComponent>("GrabComponent");
}

void AGrabObjectBase::Interact_Implementation(APlayerCharacter* _player)
{
	Super::Interact_Implementation(_player);
	_player->Grab(GetStaticMesh());
}

