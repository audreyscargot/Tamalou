// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/GrabInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/InteractableObjects/GrabComponent.h"
#include "Objects/NPC/SaveableNPC.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Tamalou/Interface/InteractInterface.h"

const FName GrabSocket = FName(TEXT("HandGrip_L"));
const int SlowWalkSpeed = 300;
const int FastWalkSpeed = 600;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhysicalAnimation = CreateDefaultSubobject<UPhysicalAnimationComponent>(FName("PhysicalAnimation"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(GetMesh(), "pelvis"); //ajouter attache à un socket du mesh
	
	HandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(FName("HandleComponent"));
	
	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysConstraintComponent"));
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
	MoveGrab(); //modifier et mettre un activate Tick à la place
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &APlayerCharacter::TryGrab);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, this, &APlayerCharacter::Uninteract);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::TryInteract);
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

void APlayerCharacter::DoJump()
{
	Jump();
}

void APlayerCharacter::TryGrab()
{
	CheckForInteract(true);
}

void APlayerCharacter::TryInteract()
{
	CheckForInteract(false);
}

//Interaction system
void APlayerCharacter::CheckForInteract(bool _isGrab)
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
	
	if (_isGrab)
	{
		InteractGrab();
		return;
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

void APlayerCharacter::InteractGrab()
{
	if (interactableObject && interactableObject->Implements<UGrabInterface>())
	{
		IGrabInterface::Execute_Grab(interactableObject, this);
	}
}

void APlayerCharacter::Grab(UPrimitiveComponent* _grabComponent)
{
	GetMesh()->SetAllBodiesBelowSimulatePhysics("hand_l", false, true);
	FVector _grabLocation = GetMesh()->GetSocketLocation("hand_l");
	GetPhysicHandle()->GrabComponentAtLocation(_grabComponent, "hand_l", _grabLocation);
	GetCapsuleComponent()->IgnoreActorWhenMoving(_grabComponent->GetOwner(),true);
	UpdateSpeed();
}

void APlayerCharacter::MoveGrab()
{
	if (HandleComponent->GetGrabbedComponent())
	{
		HandleComponent->GetGrabbedComponent()->SetPhysicsLinearVelocity(GetVelocity());
		HandleComponent->SetTargetLocation(GetMesh()->GetSocketLocation(GrabSocket));
	}
}

void APlayerCharacter::Uninteract()
{
	if (HandleComponent->GetGrabbedComponent())
	{
		UGrabComponent* _tempGrab = HandleComponent->GetGrabbedComponent()->GetOwner()->FindComponentByClass<UGrabComponent>();
		if (_tempGrab)
		{
			_tempGrab->UnGrab();
		}
		HandleComponent->ReleaseComponent();
		UpdateSpeed();
	}
}

UPhysicsHandleComponent* APlayerCharacter::GetPhysicHandle()
{
	return HandleComponent;
}

void APlayerCharacter::UpdateSpeed()
{
	if (HandleComponent->GetGrabbedComponent() && HandleComponent->GetGrabbedComponent()->GetOwner()->IsA<ASaveableNPC>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Class is %s"), *ASaveableNPC::StaticClass()->GetName());
		GetCharacterMovement()->MaxWalkSpeed = SlowWalkSpeed;
	}
	else GetCharacterMovement()->MaxWalkSpeed = FastWalkSpeed;
}

void APlayerCharacter::QuickReload()
{
	
	UGameplayStatics::OpenLevel(GetWorld(),"LvlTest_Audrey", true);
}

