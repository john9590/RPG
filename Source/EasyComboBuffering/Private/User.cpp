// Fill out your copyright notice in the Description page of Project Settings.


#include "User.h"

// Sets default values
AUser::AUser()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isgroggy = false;
	HP = MaxHP;
}

void AUser::Hit(float damage)
{
	HP -= damage;
}

void AUser::Groggy(float time)
{
	remaingroggy = time;
	isgroggy = true;
}

// Called when the game starts or when spawned
void AUser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUser::Tick(float DeltaTime)
{
	if (isgroggy) {
		remaingroggy -= DeltaTime;
		if (remaingroggy <= 0.0f) isgroggy = false;
	}
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

