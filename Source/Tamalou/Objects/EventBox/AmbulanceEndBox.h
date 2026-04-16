// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetSystemLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbulanceEndBox.generated.h"

class UBoxComponent;

UCLASS()
class TAMALOU_API AAmbulanceEndBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxCollision;

public:
	// Sets default values for this actor's properties
	AAmbulanceEndBox();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float countdownForWin = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FTimerHandle countdownTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int patientsNeeded;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int currentPatientsIn = 0;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable)
	virtual void StartCountdown();
	
	UFUNCTION(BlueprintCallable)
	bool CheckCount();
	
	UFUNCTION(BlueprintCallable)
	virtual void ChangePatientCount(int _count);

	/**
	 * Penser à ajouter Add Parent Function just après l'exec de l'event !
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndFunction();
};
