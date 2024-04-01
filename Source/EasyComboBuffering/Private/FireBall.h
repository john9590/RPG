// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "User.h"
#include "FireBall.generated.h"

UCLASS()
class AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBall();
	void Throw(FVector pSpeed, float ptime);
	void Explosion();
	void Prediction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	USphereComponent* sphere;
private:
	USceneComponent* DefaultScene;
	UParticleSystemComponent* ParticleSystem;
	UParticleSystemComponent* WarningSystem;
	bool isThrow;
	float time;
	float curtime;
	FVector Speed;
	UPROPERTY(EditAnywhere)
	AUser* User;
};
