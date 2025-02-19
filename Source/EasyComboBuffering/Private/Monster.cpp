// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Hp = 0.f;
	MaxHp = 0.f;
	Mp = 0.f;
	MaxMp = 0.f;
}

void AMonster::Damaged(float damage) {
	Hp -= damage;
	if (!AIController) {
		AController* c = GetController();
		if (c)
		{
			AIController = Cast<AMonsterAI>(c);
		}
	}
	if (AIController) {
		AIController->GetHit();
		if (Hp <= 0.f) {
			AIController->GetDied();
		}
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	Mp = MaxMp;
	Hp = MaxHp;
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

