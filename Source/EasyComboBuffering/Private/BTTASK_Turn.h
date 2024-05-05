// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DragonAI.h"
#include "Dragon.h"
#include "User.h"
#include "BTTASK_Turn.generated.h"

/**
 * 
 */
UCLASS()
class UBTTASK_Turn : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTASK_Turn();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	FRotator TargetRot;
};
