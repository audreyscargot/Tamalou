// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableObject.h"

#include "DestroyableComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ABreakableObject::ABreakableObject()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	
	DestroyableComponent = CreateDefaultSubobject<UDestroyableComponent>(TEXT("DestroyableComponent"));
	
	BoxCollision->SetNotifyRigidBodyCollision(true);
	BoxCollision->OnComponentHit.AddDynamic(this, &ABreakableObject::OnComponentHit);
}

void ABreakableObject::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (ConditionChecked())
	{
		
	}
}

bool ABreakableObject::ConditionChecked_Implementation()
{
	return true;
}

