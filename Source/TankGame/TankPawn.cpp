// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicatingMovement(true);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TankRotation == 0 && TankForward == 0)
		return;
	if (TankForward != 0)
	{
		*ForwardForce = TankForward * MovementSpeed * DeltaTime;
		AddMovementInput(GetActorForwardVector(), *ForwardForce, false);
	}
	if (TankRotation != 0)
	{
		(*RotationForce).Yaw = TankRotation * RotationSpeed * DeltaTime + GetActorRotation().Yaw;
		SetActorRotation(*RotationForce);
	}
	if (!HasAuthority())
	{
		Server_UpdatePosition(GetActorTransform(), this);
	}
}
void ATankPawn::Server_UpdatePosition_Implementation(FTransform NewPosition, ATankPawn* TankPawn)
{
	(*TankPawn).SetActorTransform(NewPosition, false, nullptr, ETeleportType::TeleportPhysics);
}
void ATankPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATankPawn, Health);
	DOREPLIFETIME(ATankPawn, PlayerID);
	DOREPLIFETIME(ATankPawn, PlayerMaterial);
}
// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ATankPawn::MoveRight);
}

void ATankPawn::MoveForward(float Value)
{
	TankForward = FMath::Clamp(Value, -1.0f, 1.0f);
}

void ATankPawn::MoveRight(float Value)
{
	TankRotation = FMath::Clamp(Value, -1.0f, 1.0f);
}
