// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	sphere->AttachToComponent(DefaultScene, FAttachmentTransformRules::KeepRelativeTransform);
	sphere->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	//sphere->SetSimulatePhysics(true);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBallAsset(TEXT("P_ky_fireBall'/Game/FXVarietyPack/Particles/P_ky_fireBall'"));
	if (FireBallAsset.Succeeded()) ParticleSystem->SetTemplate(FireBallAsset.Object);
	ParticleSystem->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	isThrow = false;
}

void AFireBall::Throw(FVector pSpeed, float ptime)
{
	isThrow = true;
	time = ptime;
	curtime = 0.0f;
	Speed = pSpeed;
}

void AFireBall::Explosion()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBallAsset(TEXT("P_ky_explosion'/Game/FXVarietyPack/Particles/P_ky_explosion'"));
	if (FireBallAsset.Succeeded()) ParticleSystem->SetTemplate(FireBallAsset.Object);
	if ((User->GetActorLocation() - GetActorLocation()).Size() < 100.0f) User->Hit(100.0f);
	FPlatformProcess::Sleep(1.0f);
	while (!Destroy());
}

void AFireBall::Prediction()
{
	FVector PrePos = GetActorLocation();
	FVector CurSpeed = Speed;
	while (PrePos.Z > 0.0f) {
		PrePos = PrePos + CurSpeed * 0.1f;
		CurSpeed.Z -= 9.8f * 0.1f;
	}
	WarningSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> WarningAsset(TEXT("P_ky_magicCircle1'/Game/FXVarietyPack/Particles/P_ky_magicCircle1'"));
	if (WarningAsset.Succeeded()) WarningSystem->SetTemplate(WarningAsset.Object);
	WarningSystem->SetWorldLocation(PrePos);
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isThrow) {
		curtime += DeltaTime;
		if (curtime >= time) {
			Explosion();
			isThrow = false;
		}
		SetActorLocation(GetActorLocation() + Speed * DeltaTime);
		Speed.Z -= 9.8f * DeltaTime;
	}
}

