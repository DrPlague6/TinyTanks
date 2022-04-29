// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector location = GetActorLocation();
	location.Z = 50.0f;
	SetActorLocation(location);
	SetReplicateMovement(true);
	SetReplicates(true);
	bAlwaysRelevant = true;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (TankForward != 0)
	{
		FVector direction = GetActorForwardVector();
		float force = TankForward * MovementSpeed * DeltaTime;
		AddMovementInput(direction,force,false);
	}
	if (TankRotation != 0) {
		FRotator rotation = GetActorRotation();
		rotation.Yaw += TankRotation * RotationSpeed * DeltaTime;
		rotation.Roll = 0;
		rotation.Pitch = 0;
		SetActorRotation(rotation);
	}*/
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ATankPawn::MoveRight);
}
void ATankPawn::MoveForward(float Value) {
	TankForward = FMath::Clamp(Value, -1.0f, 1.0f);
}
void ATankPawn::MoveRight(float Value) {
	TankRotation = FMath::Clamp(Value,-1.0f,1.0f);
}
