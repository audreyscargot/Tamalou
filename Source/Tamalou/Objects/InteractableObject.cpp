// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

#include "Components/SphereComponent.h"


// Sets default values
AInteractableObject::AInteractableObject()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

UStaticMeshComponent* AInteractableObject::GetStaticMesh()
{
	return StaticMesh;
}

void AInteractableObject::Interact_Implementation(APlayerCharacter* _player)
{
	IInteractInterface::Interact_Implementation(_player);
}

