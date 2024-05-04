// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Damaged.h"

UBT_Damaged::UBT_Damaged()
{
	NodeName = TEXT("Damaged");
}

EBTNodeResult::Type UBT_Damaged::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Target = Cast<AUser>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADragonAI::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;
	//float Damage = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ADragonAI::DamageKey);
	Target->Hit(10.0f);
	return EBTNodeResult::Succeeded;
}
