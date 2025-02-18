// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTASK_Scream.h"

UBTTASK_Scream::UBTTASK_Scream()
{
	NodeName = TEXT("SCREAM");
}

EBTNodeResult::Type UBTTASK_Scream::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Target = Cast<AUser>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADragonAI::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	Target->Groggy(1.0f);

	return EBTNodeResult::Succeeded;
}
