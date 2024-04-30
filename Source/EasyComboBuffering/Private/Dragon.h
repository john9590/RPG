// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FireBall.h"
#include "User.h"
#include "DragonAI.h"
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

enum ESkill {
	mvidx,
	amidx,
	afidx,
	scidx
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
	void isPlayingoff();
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
	UPROPERTY(EditAnywhere)
	TArray<UAnimationAsset*> animes;
	FVector Direction;
	ESkill skillidx;
	bool isMoving;
	AFireBall* fireball;
	float mvamount;
	UPROPERTY(EditAnywhere)
	float w_speed;
	bool isPlaying;
	FTimerHandle TimerHandler;
	UPROPERTY(EditAnywhere)
	float fb_time;
	AUser* player;
};
