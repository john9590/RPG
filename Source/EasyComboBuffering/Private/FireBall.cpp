// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	UE_LOG(LogTemp, Log, TEXT("Constructor"));
	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	//sphere->AttachToComponent(DefaultScene, FAttachmentTransformRules::KeepRelativeTransform);
	//sphere->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	//sphere->SetSimulatePhysics(true);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = ParticleSystem;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBallAsset(TEXT("P_ky_fireBall'/Game/FXVarietyPack/Particles/P_ky_fireBall'"));
	ky_explosion = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/FXVarietyPack/Particles/P_ky_explosion.P_ky_explosion"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> explosionAsset(TEXT("P_ky_explosion'/Game/FXVarietyPack/Particles/P_ky_explosion'"));
	if (FireBallAsset.Succeeded()) ParticleSystem->SetTemplate(FireBallAsset.Object);
	ParticleSystem->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	isThrow = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AFireBall::Throw(FVector pSpeed, float ptime)
{
	isThrow = true;
	time = ptime + 2.0f;
	curtime = 0.0f;
	Speed = pSpeed;
}

void AFireBall::FbDestory()
{
	while (!Destroy());
}

void AFireBall::Explosion()
{
	//UParticleSystem* temp = LoadObject<UParticleSystem>(nullptr, TEXT("P_ky_explosion'/Game/FXVarietyPack/Particles/P_ky_explosion'"));
	if (ky_explosion) ParticleSystem->SetTemplate(ky_explosion);
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &AFireBall::FbDestory, 1.0f, false);
	//if ((player->GetActorLocation() - GetActorLocation()).Size() < 100.0f) player->Hit(100.0f);
	//FPlatformProcess::Sleep(1.0f);
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
	//player = Cast<AUser>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("FireballTick"));
	if (isThrow) {
		curtime += DeltaTime;
		FVector Direction = GetActorLocation() - UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
		if (Direction.Length() < 100.0f) {
			Explosion();
			isThrow = false;
			return;
		}
		if (GetActorLocation().Z < -100.0f) {
			FbDestory();
			isThrow = false;
			return;
		}
		SetActorLocation(GetActorLocation() + Speed * DeltaTime);
		Speed.Z -= 5.0f * 9.8f * DeltaTime;
	}
}

