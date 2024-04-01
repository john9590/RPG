// Fill out your copyright notice in the Description page of Project Settings.


#include "dragons.h"

// Sets default values
Adragons::Adragons()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Adragons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Adragons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Adragons::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

