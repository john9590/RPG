// Fill out your copyright notice in the Description page of Project Settings.


#include "Dragon.h"

// Sets default values
ADragon::ADragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skills.Add(FSkill(100.0f, 100.0f, 100.0f, 1));
	Direction = FVector(0.0f, 0.0f, 0.0f);
	isMoving = true;
}

// Called when the game starts or when spawned
void ADragon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADragon::Move()
{
	if (isMoving) return;
	if (skills[mvidx].anime) GetMesh()->PlayAnimation(skills[mvidx].anime, true);
	AddMovementInput(Direction.GetSafeNormal(), 10.0f, true);
	isMoving = true;
}

void ADragon::Stop()
{
	AddMovementInput(FVector(0.0f, 0.0f, 0.0f), 0.0f, false); //다른 함수 있으면 쓸 것
	GetMesh()->Stop();
	isMoving = false;
}

void ADragon::AttackMouth()
{
	Stop();
	if (skills[amidx].anime) GetMesh()->PlayAnimation(skills[amidx].anime, false);
	FPlatformProcess::Sleep(0.5f);
	//이때 플레이어가 일정 거리 안에 있으면 데미지
	if ((User->GetActorLocation() - GetActorLocation()).Size() < 100.0f) User->Hit(10.0f);
}

void ADragon::AttackFireBall()
{
	Stop();
	if (skills[afidx].anime) GetMesh()->PlayAnimation(skills[afidx].anime, false);
	FPlatformProcess::Sleep(0.5f);
	fireball = CreateDefaultSubobject<AFireBall>(TEXT("FireBall"));
	fireball->SetActorLocation(GetActorLocation());
	float distance = FVector2D(Direction.X, Direction.Y).Length();
	float time = 100.0f;
	float xyspeed = distance / time;
	float zspeed = abs(Direction.Z / time) + 0.5f * time * 9.8f;
	float x = xyspeed * Direction.X / distance;
	float y = xyspeed * Direction.Y / distance;
	fireball->Throw(FVector(x, y, zspeed), time);
	//fireball->sphere->AddForce(FVector(-100000.0f, 0.0f, 100000.0f));
}

void ADragon::Scream()
{
	Stop();
	if (skills[scidx].anime) GetMesh()->PlayAnimation(skills[scidx].anime, false);
	FPlatformProcess::Sleep(0.5f);
	//이때 플레이어가 일정 거리 안에 있으면 그로기
	if ((User->GetActorLocation() - GetActorLocation()).Size() < 100.0f) User->Groggy(3.0f);
}

void ADragon::CallSkill(ESkill i)
{
	//Move는 캔슬 가능 나머지는 캔슬 불가능
	switch (i) {
		case mvidx:
			Move();
			break;
		case amidx:
			AttackMouth();
			break;
		case afidx:
			AttackFireBall();
			break;
		default:
			break;
	}
}

// Called every frame
void ADragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Cooltime, Distance, MP Append
	MP += DeltaTime;
	TArray<int> avskill;
	for (int i = 0; i < skills.Num(); i++) skills[i].curcool += DeltaTime;
	//Playing animation without Moving wait until it finished
	if (!isMoving && GetMesh()->IsPlaying()) return;
	int randvalue = 0;
	Direction = GetActorLocation() - UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	float distance = Direction.Length();
	for (int i = 0; i < skills.Num(); i++) {
		if (skills[i].cool > skills[i].curcool) continue;
		if (skills[i].distance > distance) continue;
		if (skills[i].MP > MP) continue;
		avskill.Add(i);
		randvalue += skills[i].rand;
	}
	randvalue = FGenericPlatformMath::Rand() % randvalue;
	for (int i : avskill) {
		if (skills[i].rand < randvalue) {
			CallSkill((ESkill)i);
			return;
		}
		randvalue -= skills[i].rand;
	}
}

