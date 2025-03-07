// Fill out your copyright notice in the Description page of Project Settings.


#include "User.h"
#include "TimerManager.h"

// Sets default values
AUser::AUser()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isgroggy = false;
	MaxHP = 100.f;
	HP = MaxHP;
	Attack = 1.f;
	Defense = 0.f;
}

void AUser::Hit(float damage)
{
	HP -= damage;
}

void AUser::Groggy(float time)
{
	remaingroggy = time;
	isgroggy = true;
}

void AUser::SetBuff(float enhance, float time, int idx)
{
	FTimerHandle TimerHandle;
	if (enhance == 1.f) return;
	bool isinlist = false;
	for (int i = 0; i < buffq.size();i++) {
		if (buffq[i].first == idx) {
			buffq[i].second++;
			isinlist = true;
		}
	}
	if (!isinlist) {
		Attack *= enhance;
		buffq.push_back(std::pair<int, int>(idx, 1));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, idx , enhance]()
		{
			for (int i = 0; i < buffq.size(); i++) {
				if (buffq[i].first == idx) {
					buffq[i].second--;
					if (buffq[i].second <= 0) {
						Attack /= enhance;
						buffq.erase(buffq.begin() + i);
						break;
					}
				}
			}
		}, time, false);
}

// Called when the game starts or when spawned
void AUser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUser::Tick(float DeltaTime)
{
	if (isgroggy) {
		remaingroggy -= DeltaTime;
		if (remaingroggy <= 0.0f) isgroggy = false;
	}
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

