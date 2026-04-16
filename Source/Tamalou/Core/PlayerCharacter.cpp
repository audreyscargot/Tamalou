// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <rapidjson/document.h>

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
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
	SphereComponent->SetupAttachment(GetMesh(), "pelvis"); //ajouter attache à un socket du mesh
	
	HandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(FName("HandleComponent"));
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
	MoveGrab();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::CheckForInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerCharacter::Uninteract);
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
	SphereComponent->GetOverlappingActors(OverlappingActors);
	if (OverlappingActors.Num() > 0)
	{
		float _tempDist;
		AActor* _objectToInteract = Cast<AActor>(UGameplayStatics::FindNearestActor(GetActorLocation(),OverlappingActors, _tempDist));
		if ((!interactableObject || _objectToInteract != interactableObject) && _objectToInteract)
		{
			interactableObject = _objectToInteract; //register object that can be interacted with
		}
	}
	else
	{
		interactableObject = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("No interactable objects found"));
	}
	Interact();
}

void APlayerCharacter::Interact()
{
	if (interactableObject && interactableObject->Implements<UInteractInterface>())
	{
		IInteractInterface::Execute_Interact(interactableObject, this);
	}
}

void APlayerCharacter::Grab(UPrimitiveComponent* _grabComponent)
{
	// _grabComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GetMesh()->GetSocketBoneName("hand_r"));
	GetPhysicHandle()->GrabComponentAtLocation(_grabComponent, "hand_r", GetMesh()->GetSocketLocation("carrySocket"));
	// GetPhysicHandle()->GrabComponentAtLocationWithRotation(_grabComponent,"pelvis", GetMesh()->GetComponentLocation(), FRotator(0,90, GetActorRotation().Yaw));
	GetCapsuleComponent()->IgnoreActorWhenMoving(_grabComponent->GetOwner(),true);
}

void APlayerCharacter::MoveGrab()
{
	if (HandleComponent->GetGrabbedComponent())
	{
		HandleComponent->SetTargetLocation(GetMesh()->GetSocketLocation("carrySocket"));
	}
}

void APlayerCharacter::Uninteract()
{
	if (HandleComponent->GetGrabbedComponent())
	{
		HandleComponent->ReleaseComponent();
	}
}

UPhysicsHandleComponent* APlayerCharacter::GetPhysicHandle()
{
	return HandleComponent;
}

