// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Prediction.generated.h"

UCLASS()
class APrediction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrediction();

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
	float spawntime;
};
