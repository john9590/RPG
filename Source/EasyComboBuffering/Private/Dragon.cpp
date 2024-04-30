// Fill out your copyright notice in the Description page of Project Settings.


#include "Dragon.h"

// Sets default values
ADragon::ADragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	skills.Add(FSkill(0.0f, 100000.0f, 0.0f, 1));
	skills.Add(FSkill(3.0f, 500.0f, 0.0f, 1));
	skills.Add(FSkill(5.0f, 100000.0f, 1.0f, 1));
	Direction = FVector(0.0f, 0.0f, 0.0f);
	isMoving = false;
	isPlaying = false;
	player = Cast<AUser>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
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
	UE_LOG(LogTemp, Log, TEXT("%f"), mvamount);
	if (isMoving) return;
	if (animes[mvidx]) GetMesh()->PlayAnimation(animes[mvidx], true);
	//GetMovementComponent()->AddRadialForce(Direction.GetSafeNormal(), 1.0f, 1.0f, ERadialImpulseFalloff::RIF_Constant);
	//AddMovementInput(Direction.GetSafeNormal(), -1.0f, true);
	isMoving = true;
}

void ADragon::Stop()
{
	GetMesh()->Stop();
	isMoving = false;
}

void ADragon::isPlayingoff()
{
	isPlaying = false;
}

void ADragon::AttackMouth()
{
	//Stop();
	isMoving = false;
	isPlaying = true;
	skills[amidx].curcool = 0.0f;
	FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
	SetActorRotation(GetRot.Rotation() + FRotator(0.0f, 90.0f, 0.0f));
	if (animes[amidx]) GetMesh()->PlayAnimation(animes[amidx], false);
	//FPlatformProcess::Sleep(0.5f);
	//�̶� �÷��̾ ���� �Ÿ� �ȿ� ������ ������
	if ((player->GetActorLocation() - GetActorLocation()).Size() < 500.0f) {
		player->Hit(3.0f);
		//UE_LOG(LogTemp, Log, TEXT("Hit"));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ADragon::isPlayingoff, 1.0f, false);
	//FPlatformProcess::Sleep(1.0f);
	//isPlaying = false;
}

void ADragon::AttackFireBall()
{
	//FPlatformProcess::Sleep(0.5f);
	FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
	FVector initpos = GetRot.GetSafeNormal();//(GetRot.Rotation() + FRotator(0.0f, 90.0f, 0.0f)).Vector();
	initpos = FVector(270.0f * initpos.X, 270.0f * initpos.Y, -260.0f);
	fireball = (AFireBall*)GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), GetActorLocation() - initpos, GetActorRotation());
	//if (fireball->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform)) UE_LOG(LogTemp,Log,TEXT("A"));
	///if (fireball->SetActorLocation(GetActorLocation())) UE_LOG(LogTemp,Log,TEXT("B"));
	FVector2D xyVector = -FVector2D(Direction.X - initpos.X, Direction.Y - initpos.Y);
	float distance = FMath::Max(xyVector.Length(), 0.001f);
	float xyspeed = distance / fb_time;
	float zspeed = (-Direction.Z + initpos.Z)/ fb_time + 2.5f * fb_time * 9.8f;
	float x = xyspeed * xyVector.GetSafeNormal().X;
	float y = xyspeed * xyVector.GetSafeNormal().Y;
	fireball->Throw(FVector(x, y, zspeed), fb_time);
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ADragon::isPlayingoff, 1.0f, false);
	UE_LOG(LogTemp, Log, TEXT("%f %f"), initpos.X, initpos.Y);
	//fireball->sphere->AddForce(FVector(-100000.0f, 0.0f, 100000.0f));
}

void ADragon::Scream()
{
	Stop();
	if (skills[scidx].anime) GetMesh()->PlayAnimation(skills[scidx].anime, false);
	FPlatformProcess::Sleep(0.5f);
	//�̶� �÷��̾ ���� �Ÿ� �ȿ� ������ �׷α�
	if ((player->GetActorLocation() - GetActorLocation()).Size() < 100.0f) player->Groggy(3.0f);
}

void ADragon::CallSkill(ESkill i)
{
	FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
	//Move�� ĵ�� ���� �������� ĵ�� �Ұ���
	//UE_LOG(LogTemp, Log, TEXT("dhodksehoTLqkf"));
	switch (i) {
		case mvidx:
			Move();
			break;
		case amidx:
			AttackMouth();
			break;
		case afidx:
			isMoving = false;
			isPlaying = true;
			skills[afidx].curcool = 0.0f;
			SetActorRotation(GetRot.Rotation() + FRotator(0.0f, 90.0f, 0.0f));
			if (animes[afidx]) GetMesh()->PlayAnimation(animes[afidx], false);
			GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ADragon::AttackFireBall, 0.5f, false);
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
	//GetMovementComponent()->AddInputVector(FVector(-1.0f, 0.0f, 0.0f));
	for (int i = 0; i < skills.Num(); i++) skills[i].curcool += DeltaTime;
	//if (fireball) fireball->Tick(DeltaTime);
	//Playing animation without Moving wait until it finished
	//if (!isMoving && GetMesh()->IsPlaying()) return;
	if (isPlaying) return;
	int randvalue = 0;
	Direction = GetActorLocation() - player->GetActorLocation();
	float distance = Direction.Length();
	for (int i = 0; i < skills.Num(); i++) {
		if (skills[i].cool > skills[i].curcool) continue;
		if (skills[i].distance < distance) continue;
		if (skills[i].MP > MP) continue;
		avskill.Add(i);
		randvalue += skills[i].rand;
	}
	//UE_LOG(LogTemp, Log, TEXT("%d"),randvalue);
	//Move();
	//CallSkill(afidx);
	if (randvalue > 0) {
		randvalue = FGenericPlatformMath::Rand() % randvalue;
		UE_LOG(LogTemp, Log, TEXT("%d"), randvalue);
		for (int i : avskill) {
			if (skills[i].rand > randvalue) {
				CallSkill((ESkill)i);
				return;
			}
			randvalue -= skills[i].rand;
		}
	}
	
}

