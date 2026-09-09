// Fill out your copyright notice in the Description page of Project Settings.


#include "Key.h"


// Sets default values
ADoorKey::ADoorKey()
{
	
}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoorKey::Grab_Implementation(APlayerCharacter* _player)
{
	Super::Grab_Implementation(_player);
}

