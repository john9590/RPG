// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FireBall.h"
#include "Dragon.generated.h"

USTRUCT()
struct FSkill {
	GENERATED_BODY()
public:
	FSkill() { curcool = 0.0f; }
	FSkill(float pcool, float pdistance, float pMP, int prand) {
		cool = pcool;
		distance = pdistance;
		MP = pMP;
		rand = prand;
		curcool = 0.0f;
	}
	float cool;
	float distance;
	float curcool;
	float MP;
	int rand;
	UAnimationAsset* anime;
};

UCLASS()
class ADragon : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADragon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move();
	void Stop();
	void AttackMouth();
	void AttackFireBall();
	void Scream();
	void CallSkill(ESkill i);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float MP;
	UPROPERTY(EditAnywhere)
	float MaxMP;
	//UPROPERTY(EditAnywhere)
	TArray<FSkill> skills;
	FVector Direction;
	ESkill skillidx;
	bool isMoving;
	AFireBall* fireball;
	AUser* User;
};

enum ESkill {
	mvidx,
	amidx,
	afidx,
	scidx
};