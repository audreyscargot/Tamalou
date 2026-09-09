// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabObjectBase.h"

#include "GrabComponent.h"
#include "Components/SphereComponent.h"
#include "Core/PlayerCharacter.h"


// Sets default values
AGrabObjectBase::AGrabObjectBase()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(StaticMesh);
	SphereComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	
	GrabComponent = CreateDefaultSubobject<UGrabComponent>("GrabComponent");
	GrabComponent->SetOwner(this);
}

void AGrabObjectBase::BeginPlay()
{
	Super::BeginPlay();
	GrabComponent->SetOwner(this);
}

UStaticMeshComponent* AGrabObjectBase::GetStaticMesh()
{
	return StaticMesh;
}

void AGrabObjectBase::Grab_Implementation(APlayerCharacter* _player)
{
	if (GrabComponent && GetStaticMesh())
	{
		GrabComponent->Grab(_player);
		_player->Grab(GetStaticMesh());
		SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	};
}

void AGrabObjectBase::IsUnGrabbed()
{
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}

