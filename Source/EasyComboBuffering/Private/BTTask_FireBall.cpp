// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FireBall.h"

UBTTask_FireBall::UBTTask_FireBall()
{
	NodeName = TEXT("AttackFireball");
}

EBTNodeResult::Type UBTTask_FireBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto player = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADragonAI::TargetKey));
	if (nullptr == player)
		return EBTNodeResult::Failed;
	auto Dragon = OwnerComp.GetAIOwner()->GetPawn();
	float fb_time = 5.0f;
	FVector Direction = Dragon->GetActorLocation() - player->GetActorLocation();
	FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
	FVector initpos = GetRot.GetSafeNormal();//(GetRot.Rotation() + FRotator(0.0f, 90.0f, 0.0f)).Vector();
	initpos = FVector(270.0f * initpos.X, 270.0f * initpos.Y, -260.0f);
	AFireBall* fireball = (AFireBall*)GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), Dragon->GetActorLocation() - initpos, Dragon->GetActorRotation());
	//if (fireball->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform)) UE_LOG(LogTemp,Log,TEXT("A"));
	///if (fireball->SetActorLocation(GetActorLocation())) UE_LOG(LogTemp,Log,TEXT("B"));
	FVector2D xyVector = -FVector2D(Direction.X - initpos.X, Direction.Y - initpos.Y);
	float distance = FMath::Max(xyVector.Length(), 0.001f);
	float xyspeed = distance / fb_time;
	float zspeed = (-Direction.Z + initpos.Z) / fb_time + 2.5f * fb_time * 19.6f;
	float x = xyspeed * xyVector.GetSafeNormal().X;
	float y = xyspeed * xyVector.GetSafeNormal().Y;
	fireball->Throw(FVector(x, y, zspeed), fb_time);
	return EBTNodeResult::Succeeded;
}
