// Fill out your copyright notice in the Description page of Project Settings.


#include "Dragon.h"

// Sets default values
ADragon::ADragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skills.Add(FSkill(0.0f, 0.0f, 0.0f, 1));
	Direction = FVector(0.0f, 0.0f, 0.0f);
	isMoving = false;
}

// Called when the game starts or when spawned
void ADragon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADragon::Move()
{
	FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
	AddMovementInput(GetRot.GetSafeNormal(), -mvamount * w_speed, true);
	SetActorRotation(GetRot.Rotation() + FRotator(0.0f, 90.0f, 0.0f));
	//UE_LOG(LogTemp, Log, TEXT("%f"), mvamount);
	if (isMoving) return;
	GetMesh()->PlayAnimation(animes[mvidx], true);
	//GetMovementComponent()->AddRadialForce(Direction.GetSafeNormal(), 1.0f, 1.0f, ERadialImpulseFalloff::RIF_Constant);
	//AddMovementInput(Direction.GetSafeNormal(), -1.0f, true);
	isMoving = true;
}

void ADragon::Stop()
{
	AddMovementInput(FVector(0.0f, 0.0f, 0.0f), 0.0f, false); //
	GetMesh()->Stop();
	isMoving = false;
}

void ADragon::AttackMouth()
{
	Stop();
	if (skills[amidx].anime) GetMesh()->PlayAnimation(skills[amidx].anime, false);
	FPlatformProcess::Sleep(0.5f);
	//�̶� �÷��̾ ���� �Ÿ� �ȿ� ������ ������
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
	distance = FMath::Max(0.001f, distance);
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
	//�̶� �÷��̾ ���� �Ÿ� �ȿ� ������ �׷α�
	if ((User->GetActorLocation() - GetActorLocation()).Size() < 100.0f) User->Groggy(3.0f);
}

void ADragon::CallSkill(ESkill i)
{
	//Move�� ĵ�� ���� �������� ĵ�� �Ұ���
	UE_LOG(LogTemp, Log, TEXT("dhodksehoTLqkf"));
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
	//UE_LOG(LogTemp, Log, TEXT("rand"));
	MP += DeltaTime;
	mvamount = DeltaTime;
	TArray<int> avskill;
	for (int i = 0; i < skills.Num(); i++) skills[i].curcool += DeltaTime;
	//Playing animation without Moving wait until it finished
	//if (!isMoving && GetMesh()->IsPlaying()) return;
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
	//UE_LOG(LogTemp, Log, TEXT("rand"));
	//Move();
	CallSkill((ESkill)0);
	if (randvalue > 0) {
		randvalue = FGenericPlatformMath::Rand() % randvalue;
		for (int i : avskill) {
			if (skills[i].rand < randvalue) {
				CallSkill((ESkill)i);
				return;
			}
			randvalue -= skills[i].rand;
		}
	}
}

