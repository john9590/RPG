// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "MonsterHP.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Hp = 0.f;
	MaxHp = 0.f;
	Mp = 0.f;
	MaxMp = 0.f;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsule->SetCollisionProfileName(TEXT("BlockAll"));
	RootComponent = capsule;
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	// 2. SkeletalMeshComponent���� �ٸ� �浹�� ��� ��

	capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);  // �ٸ� `Pawn`�� �浹 ���
	//capsule->SetupAttachment(RootComponent);
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(RootComponent); 
	HPBarWidget->SetWidgetSpace(EWidgetSpace::World);
	HPBarWidget->SetDrawSize(FVector2D(150, 20));
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 50.f)); // �θ� ���� ��� ��ġ
	HPBarWidget->SetRelativeRotation(FRotator(0.f, 90.f, 0.f)); // �θ� ���� ��� ȸ��
	HPBarWidget->SetSimulatePhysics(false);  // ���� �ùķ��̼� ��Ȱ��ȭ
}

void AMonster::Damaged(float damage) {
	Hp -= damage;
	if (HPBarWidget)
	{
		UMonsterHP* HPBar = Cast<UMonsterHP>(HPBarWidget->GetWidget());
		if (HPBar)
		{
			HPBar->SetHP(Hp/MaxHp);
		}
	}
	if (!AIController) {
		AController* c = GetController();
		if (c)
		{
			AIController = Cast<AMonsterAI>(c);
		}
	}
	if (AIController) {
		AIController->GetHit();
		if (Hp <= 0.f) {
			AIController->GetDied();
		}
	}
}

float AMonster::GetHp()
{
	return Hp;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	Mp = MaxMp;
	Hp = MaxHp;
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

