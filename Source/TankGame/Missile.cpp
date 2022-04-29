// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	_sleep(1);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rotation = GetVelocity().Rotation();
	rotation.Roll = 0.0f;
	rotation.Pitch = 0.0f;
	SetActorRotation(rotation);
}

