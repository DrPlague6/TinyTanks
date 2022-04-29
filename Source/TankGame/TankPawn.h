// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "TankPawn.generated.h"

UCLASS()
class TANKGAME_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	UPROPERTY(EditAnywhere, Category = "Tank")
		float MovementSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Tank")
		float RotationSpeed = 30.0f;
private:
	UStaticMeshComponent* TankMeshComponent;
	float TankForward;
	USceneComponent* Root;
	float TankRotation;
};
