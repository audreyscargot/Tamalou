// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbulanceEndBox.h"

#include "Components/BoxComponent.h"
#include "Core/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Objects/NPC/SaveableNPC.h"


// Sets default values
AAmbulanceEndBox::AAmbulanceEndBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmbulanceEndBox::BeginOverlap);
	}
}

// Called when the game starts or when spawned
void AAmbulanceEndBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmbulanceEndBox::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherOverlappedComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASaveableNPC* _NPC = Cast<ASaveableNPC>(OtherOverlappedComp->GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *OtherActor->GetName())
	if (_NPC)
	{
		ChangePatientCount(1);
		if (CheckCount())
		{
			StartCountdown();
		}
	}
}

void AAmbulanceEndBox::StartCountdown()
{
	UKismetSystemLibrary::K2_SetTimer(this, "EndFunction", countdownForWin, false, false, 0,0);
}

bool AAmbulanceEndBox::CheckCount()
{
	if (currentPatientsIn == patientsNeeded)
	{
		return true;
	}
	return false;
}

/**
 * @param _count : test
 */
void AAmbulanceEndBox::ChangePatientCount(int _count)
{
	currentPatientsIn += _count;
}


void AAmbulanceEndBox::EndFunction_Implementation()
{
	if (!CheckCount()) return;
}



