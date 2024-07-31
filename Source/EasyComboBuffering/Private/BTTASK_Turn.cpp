// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTASK_Turn.h"

UBTTASK_Turn::UBTTASK_Turn()
{
	bNotifyTick = true;
	NodeName = TEXT("Turn");
	TargetRot = FRotator(0.f, 0.f, 0.f);
}

EBTNodeResult::Type UBTTASK_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ABCharacter = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ABCharacter)
		return EBTNodeResult::Failed;

	auto Target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADragonAI::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	//Ÿ���� ��ġ�� ������ġ�� ���� ���⺤�͸� �����?
	FVector LockVector = Target->GetActorLocation() - ABCharacter->GetActorLocation();
	LockVector.Z = 0.0f;
	TargetRot = LockVector.Rotation(); //���⺤�ͷκ��� ������ ����?����?)
	//������ŭ 2�ʿ� ���ļ� ȸ����Ų��.
	//ABCharacter->SetActorRotation(TargetRot);
	//ABCharacter->SetActorRotation(FMath::RInterpTo(ABCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
	//while (!ABCharacter->GetActorRotation().Equals(TargetRot, 1.0f));
	return EBTNodeResult::InProgress;
}

void UBTTASK_Turn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	//UE_LOG(LogTemp, Log, TEXT("TickTask"));
	auto ABCharacter = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ABCharacter) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	ABCharacter->SetActorRotation(FMath::RInterpTo(ABCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
	if (ABCharacter->GetActorRotation().Equals(TargetRot,1.0f)) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}