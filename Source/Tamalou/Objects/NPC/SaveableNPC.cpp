// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveableNPC.h"

#include "Components/SphereComponent.h"
#include "Tamalou/Core/PlayerCharacter.h"

const FName SOCKET = FName(TEXT("pelvisSocket")); //ça marche paaaaaaaas

// Sets default values
ASaveableNPC::ASaveableNPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetMesh());
	
}

// Called when the game starts or when spawned
void ASaveableNPC::BeginPlay()
{
	Super::BeginPlay();
	// GetMesh()->SetBodySimulatePhysics("pelvis",true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics("pelvis",true, true);
}

// Called every frame
void ASaveableNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASaveableNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASaveableNPC::Interact_Implementation(APlayerCharacter* _player)
{
	IInteractInterface::Interact_Implementation(_player);
	if (!isGrabbed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab"));
		isGrabbed = true;
		SetActorLocation(_player->GetActorLocation());
		_player->Grab(GetMesh());
	}
}

