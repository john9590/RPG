// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTASK_Turn.h"

UBTTASK_Turn::UBTTASK_Turn()
{
	NodeName = TEXT("Turn");
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

	//Ÿ���� ��ġ�� ������ġ�� ���� ���⺤�͸� �����
	FVector LockVector = Target->GetActorLocation() - ABCharacter->GetActorLocation();
	LockVector.Z = 0.0f;
	FRotator TargetRot = LockVector.Rotation(); //���⺤�ͷκ��� ������ ����(����?)
	//������ŭ 2�ʿ� ���ļ� ȸ����Ų��.
	ABCharacter->SetActorRotation(TargetRot);
	//ABCharacter->SetActorRotation(FMath::RInterpTo(ABCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 0.01f));
	
	return EBTNodeResult::Succeeded;
}
