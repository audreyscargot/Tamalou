// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <rapidjson/document.h>

#include "EnhancedInputComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "Tamalou/Interface/InteractInterface.h"
#include "Tamalou/Objects/InteractableObject.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhysicalAnimation = CreateDefaultSubobject<UPhysicalAnimationComponent>(FName("PhysicalAnimation"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PhysicalAnimation->SetSkeletalMeshComponent(GetMesh());
	PhysicalAnimation->ApplyPhysicalAnimationSettingsBelow(boneName, physAnimData, true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(boneName, true, false);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteract();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
	}
}

//Movement functions
void APlayerCharacter::Move(const FInputActionValue& _value)
{
	FVector2D _movementVector = _value.Get<FVector2D>();
	DoMove(_movementVector.X, _movementVector.Y);
	
}

void APlayerCharacter::DoMove(float _right, float _forward)
{
	if (GetController())
	{
		const FRotator _rotation = GetController()->GetControlRotation();
		const FRotator _yawRotation(0, _rotation.Yaw, 0);
		
		const FVector _forwardDirection = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::X);
		const FVector _rightDirection = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(_forwardDirection, _forward);
		AddMovementInput(_rightDirection, _right);
	}
}

//Interaction system
void APlayerCharacter::CheckForInteract()
{
	// /!\ Make sure to put collision of actor that need interaction to Interactable !!!
	TArray<AActor*> _overlappingActors;
	SphereComponent->GetOverlappingActors(_overlappingActors);
	UE_LOG(LogTemp, Warning, TEXT("%d"), _overlappingActors.Num())
	if (_overlappingActors.Num() > 0)
	{
		float _tempDist;
		AInteractableObject* _objectToInteract = Cast<AInteractableObject>(UGameplayStatics::FindNearestActor(GetActorLocation(),_overlappingActors, _tempDist));
		if (!interactableObject || _objectToInteract != interactableObject)
		{
			interactableObject = _objectToInteract; //register object that can be interacted with
		}
	}
	else if (_overlappingActors.Num() == 0)
	{
		interactableObject = nullptr;
	}
	// UE_LOG(LogTemp, Warning, TEXT("%s"), interactableObject ? *interactableObject->GetName() : nullptr)
}

void APlayerCharacter::Interact()
{
	if (interactableObject && interactableObject->Implements<UInteractInterface>())
	{
		IInteractInterface::Execute_Interact(interactableObject, this);
	}
}

