// Fill out your copyright notice in the Description page of Project Settings.


#include "Prediction.h"

// Sets default values
APrediction::APrediction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = ParticleSystem;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CircleAsset(TEXT("P_ky_magicCircle1'/Game/FXVarietyPack/Particles/P_ky_magicCircle1'"));
	if (CircleAsset.Succeeded()) ParticleSystem->SetTemplate(CircleAsset.Object);
	spawntime = 5.0f;
}

// Called when the game starts or when spawned
void APrediction::BeginPlay()
{
	Super::BeginPlay();
	spawntime = 5.0f;
	
}

// Called every frame
void APrediction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawntime -= DeltaTime;
	if (spawntime <= 0.0f) {
		while (!Destroy());
	}
}

